#include "teslimetme.h"
#include "ui_teslimetme.h"

#include <QTimer>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>


TeslimEtme::TeslimEtme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TeslimEtme)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    // Table model
    odunc_model = new QSqlTableModel(this);
    odunc_model->setTable("odunc_alinan");

    teslim_model = new QSqlTableModel(this);
    teslim_model->setTable("odunc_teslim_edilen");

    ui->odunc_table->setModel(odunc_model);
    ui->teslim_table->setModel(teslim_model);

    // Sürekli yenileme için Timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TeslimEtme::yenile);
    timer->start(6000);

    yenile();
}

TeslimEtme::~TeslimEtme()
{
    delete ui;
}


void TeslimEtme::yenile() {
    odunc_model->select();
    teslim_model->select();
}


void TeslimEtme::on_odunc_table_clicked(const QModelIndex &index)
{
    ui->uyeNo_line->setText(odunc_model->index(index.row(), 0).data().toString());
    ui->kitapNo_line->setText(odunc_model->index(index.row(), 1).data().toString());
    secili_kayit_tarih = odunc_model->index(index.row(), 2).data().toString();
}


void TeslimEtme::on_pushButton_clicked()
{
    const QString u_no = ui->uyeNo_line->text();
    const QString k_no = ui->kitapNo_line->text();
    const QDate teslim_tarih = ui->dateEdit->date();

    if (u_no.isEmpty()) {
        QMessageBox::critical(this, "Hata", "Kayıt seçiniz!");
        return;
    }

    QSqlQuery query;
    query.exec("BEGIN TRANSACTION");

    // Ödünç alınan kayıtlardan sil
    query.prepare("DELETE FROM odunc_alinan WHERE uye_no=? AND kitap_no=?");
    query.addBindValue(u_no.toInt());
    query.addBindValue(k_no.toInt());

    if (!query.exec()) {
        query.exec("ROLLBACK");
        qWarning() << "odunc_alinan tablosundan silmede hata!";
        return;
    }

    // Stok güncelle
    query.prepare("UPDATE kitap SET kitap_sayisi = kitap_sayisi + 1 WHERE kitap_no=?");
    query.addBindValue(k_no.toInt());

    if (!query.exec()) {
        query.exec("ROLLBACK");
        qWarning() << "kitap tablosu güncellemede hata!";
        return;
    }

    // Borç hesabı
    QDate odunc_tarih = QDate::fromString(secili_kayit_tarih, "dd.MM.yyyy");
    int gun_fark = odunc_tarih.daysTo(teslim_tarih);
    gun_fark -= 15;
    if (gun_fark < 0) gun_fark = 0;
    int borc = gun_fark * 4;

    // Teslim edilenlere ekle
    query.prepare(
        "INSERT INTO odunc_teslim_edilen (uye_no, kitap_no, alma_tarihi, verme_tarihi, borc)"
        "VALUES (:uye, :kitap, :alma, :verme, :borc)"
    );
    query.bindValue(":uye", u_no.toInt());
    query.bindValue(":kitap", k_no.toInt());
    query.bindValue(":alma", secili_kayit_tarih);
    query.bindValue(":verme", teslim_tarih.toString("dd.MM.yyyy"));
    query.bindValue(":borc", borc);

    if (!query.exec()) {
        query.exec("ROLLBACK");
        qWarning() << "odunc_teslim_edilen tablosuna eklemede hata!";
        return;
    }

    query.exec("COMMIT");
    yenile();
}
