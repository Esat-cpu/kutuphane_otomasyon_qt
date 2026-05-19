#include "oduncalma.h"
#include "ui_oduncalma.h"

#include <QTimer>
#include <QMessageBox>
#include <QSqlQuery>


OduncAlma::OduncAlma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OduncAlma)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    // Table Model
    uye_model = new QSqlTableModel(this);
    uye_model->setTable("uye");

    kitap_model = new QSqlTableModel(this);
    kitap_model->setTable("kitap");

    odunc_model = new QSqlTableModel(this);
    odunc_model->setTable("odunc_alinan");

    ui->uye_table->setModel(uye_model);
    ui->kitap_table->setModel(kitap_model);
    ui->odunc_table->setModel(odunc_model);

    // Sürekli yenileme için Timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &OduncAlma::yenile);
    timer->start(6000);

    yenile();
}


OduncAlma::~OduncAlma()
{
    delete ui;
}


void OduncAlma::yenile() {
    uye_model->select();
    kitap_model->select();
    odunc_model->select();
}


void OduncAlma::on_uye_table_clicked(const QModelIndex &index)
{
    ui->uyeNo_line->setText(uye_model->index(index.row(), 0).data().toString());
}


void OduncAlma::on_kitap_table_clicked(const QModelIndex &index)
{
    ui->kitapNo_line->setText(kitap_model->index(index.row(), 0).data().toString());
    secili_kitap_stok = kitap_model->index(index.row(), 2).data().toInt();
}


void OduncAlma::on_oduncAl_button_clicked()
{
    const QString _u_no = ui->uyeNo_line->text();
    const QString _k_no = ui->kitapNo_line->text();

    if (_u_no.isEmpty() || _k_no.isEmpty()) {
        QMessageBox::critical(this, "Hata", "Üye ve Kitap seçin");
        return;
    }

    const int u_no = _u_no.toInt();
    const int k_no = _k_no.toInt();
    const QString tarih = ui->dateEdit->text();

    QSqlQuery query;

    // Bu kişi bu kitabı ödünç almış mı kontrolü
    query.prepare("SELECT 1 FROM odunc_alinan WHERE uye_no= :uye_no AND kitap_no= :kitap_no");
    query.bindValue(":uye_no", u_no);
    query.bindValue(":kitap_no", k_no);
    query.exec();

    if (query.next()) {
        QMessageBox::critical(this, "Hata",
            "Bu üye bu kitabın bir tanesini şu an ödünç almış, tekrar ödünç verilemez!");
        return;
    }

    // Stok kontrolü
    query.prepare("SELECT COUNT(*) FROM odunc_alinan WHERE kitap_no= :kitap_no");
    query.bindValue(":kitap_no", k_no);
    query.exec();
    query.next();
    const int count = query.value(0).toInt();

    if (count >= secili_kitap_stok) {
        QMessageBox::critical(this, "Hata",
            "Bu kitap şu an mevcut değil, hepsi üyelere ödünç verilmiştir.");
        return;
    }

    // Ödünç alınanlara ekle
    query.prepare(
        "INSERT INTO odunc_alinan (uye_no, kitap_no, odunc_alma_tarihi) VALUES (?, ?, ?)"
    );
    query.addBindValue(u_no);
    query.addBindValue(k_no);
    query.addBindValue(tarih);
    query.exec();

    yenile();
}

