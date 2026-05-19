#include "kitapislemleri.h"
#include "ui_kitapislemleri.h"

#include <QTimer>
#include <QMessageBox>
#include <QSqlQuery>


KitapIslemleri::KitapIslemleri(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KitapIslemleri)
{
    ui->setupUi(this);

    // Table model
    kitap_model = new QSqlTableModel(this);
    kitap_model->setTable("kitap");

    odunc_model = new QSqlTableModel(this);
    odunc_model->setTable("odunc_alinan");
    odunc_model->setFilter("1=0");

    teslim_model = new QSqlTableModel(this);
    teslim_model->setTable("odunc_teslim_edilen");
    teslim_model->setFilter("1=0");

    ui->kitap_table->setModel(kitap_model);
    ui->odunc_table->setModel(odunc_model);
    ui->teslim_table->setModel(teslim_model);

    // Sürekli yenileme için Timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &KitapIslemleri::yenile);
    timer->start(6000);

    yenile();
}

KitapIslemleri::~KitapIslemleri()
{
    delete ui;
}


void KitapIslemleri::yenile() {
    kitap_model->select();
    odunc_model->select();
    teslim_model->select();
}


void KitapIslemleri::on_kitap_table_clicked(const QModelIndex &index)
{
    QVariant k_no = kitap_model->index(index.row(), 0).data();
    ui->kitapNo_line->setText(k_no.toString());
    ui->kitapAd_line->setText(kitap_model->index(index.row(), 1).data().toString());
    ui->stok_line->setText(kitap_model->index(index.row(), 2).data().toString());

    odunc_model->setFilter(QString("kitap_no = %1").arg(k_no.toInt()));
    teslim_model->setFilter(QString("kitap_no = %1").arg(k_no.toInt()));
}


void KitapIslemleri::on_yeniKayit_button_clicked()
{
    const QString k_ad = ui->kitapAd_line->text();
    const QString stok = ui->stok_line->text();

    if (k_ad.isEmpty() || stok.isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Gerekli alanları doldurunuz!");
        return;
    }

    QSqlQuery query = QSqlQuery();
    query.prepare("INSERT INTO kitap (kitap_ad, kitap_sayisi) VALUES (?, ?)");
    query.addBindValue(k_ad);
    query.addBindValue(stok.toInt());
    query.exec();

    yenile();
}


void KitapIslemleri::on_guncelle_button_clicked()
{
    const QString _k_no = ui->kitapNo_line->text();
    if (_k_no.isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Kitap Seçiniz!");
        return;
    }

    const int k_no = _k_no.toInt();
    const QString k_ad = ui->kitapAd_line->text();
    const QString stok = ui->stok_line->text();

    QSqlQuery query("UPDATE kitap SET kitap_ad=?, kitap_sayisi=? WHERE kitap_no=?");
    query.addBindValue(k_ad);
    query.addBindValue(stok);
    query.addBindValue(k_no);
    query.exec();

    yenile();
}


void KitapIslemleri::on_sil_button_clicked()
{
    const QString _k_no = ui->kitapNo_line->text();
    if (_k_no.isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Kitap Seçiniz!");
        return;
    }

    const int k_no = _k_no.toInt();

    QSqlQuery query;

    // Ödünç alınma kontrolü
    query.prepare("SELECT EXISTS(SELECT 1 FROM odunc_alinan WHERE kitap_no=?)");
    query.addBindValue(k_no);
    query.exec();
    query.next();

    if (query.value(0).toBool()) {
        QMessageBox::critical(this, "Hata",
            "Bu kitap silinemez. Bu kitap bir üyeye ödünç verilmiştir."
        );
        return;
    }

    // Silme
    query.prepare("DELETE FROM kitap WHERE kitap_no=?");
    query.addBindValue(k_no);
    query.exec();

    yenile();
}
