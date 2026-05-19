#include "uyeislemleri.h"
#include "ui_uyeislemleri.h"

#include <QTimer>
#include <QMessageBox>
#include <QSqlQuery>


UyeIslemleri::UyeIslemleri(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UyeIslemleri)
{
    ui->setupUi(this);

    // Table model
    model = new QSqlTableModel(this);
    model->setTable("uye");

    ui->tableView->setModel(model);

    // Sürekli yenileme için timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UyeIslemleri::yenile);
    timer->start(2500);

    yenile();
}

UyeIslemleri::~UyeIslemleri()
{
    delete ui;
}


void UyeIslemleri::yenile() {
    model->select();
}


void UyeIslemleri::on_tableView_clicked(const QModelIndex &index)
{
    ui->uyeNo_line->setText(model->index(index.row(), 0).data().toString());
    ui->uyeAd_line->setText(model->index(index.row(), 1).data().toString());
    ui->uyeSoyad_line->setText(model->index(index.row(), 2).data().toString());
}


void UyeIslemleri::on_yeniKayit_button_clicked()
{
    const QString u_ad = ui->uyeAd_line->text();
    const QString u_soyad = ui->uyeSoyad_line->text();

    if (u_ad.isEmpty() || u_soyad.isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Gerekli alanları doldurunuz!");
        return;
    }

    QSqlQuery query = QSqlQuery();
    query.prepare("INSERT INTO uye (uye_ad, uye_soyad) VALUES (?, ?)");
    query.addBindValue(u_ad);
    query.addBindValue(u_soyad);
    query.exec();

    yenile();
}


void UyeIslemleri::on_guncelle_button_clicked()
{
    const QString _u_no = ui->uyeNo_line->text();
    if (_u_no.isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Üye Seçiniz!");
        return;
    }

    const int u_no = _u_no.toInt();
    const QString u_ad = ui->uyeAd_line->text();
    const QString u_soyad = ui->uyeSoyad_line->text();

    QSqlQuery query("UPDATE uye SET uye_ad=?, uye_soyad=? WHERE uye_no=?");
    query.addBindValue(u_ad);
    query.addBindValue(u_soyad);
    query.addBindValue(u_no);
    query.exec();

    yenile();
}


void UyeIslemleri::on_sil_button_clicked()
{
    const QString _u_no = ui->uyeNo_line->text();
    if (_u_no.isEmpty()) {
        QMessageBox::critical(this, "Hata!", "Üye Seçiniz!");
        return;
    }

    const int u_no = _u_no.toInt();

    QSqlQuery query("DELETE FROM uye WHERE uye_no=?");
    query.addBindValue(u_no);
    query.exec();

    yenile();
}
