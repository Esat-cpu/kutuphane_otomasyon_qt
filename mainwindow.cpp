#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uyeislemleri.h"
#include "kitapislemleri.h"
#include "oduncalma.h"
#include "teslimetme.h"

static const QString DB_LOCATION = "../../sqlite.db";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // db
    database_baglan();

    // signal slot
    connect(ui->uye_label, &TiklanabilirLabel::clicked, this, &MainWindow::uye_islemleri);
    connect(ui->uye2_label, &TiklanabilirLabel::clicked, this, &MainWindow::uye_islemleri);
    connect(ui->kitap_label, &TiklanabilirLabel::clicked, this, &MainWindow::kitap_islemleri);
    connect(ui->kitap2_label, &TiklanabilirLabel::clicked, this, &MainWindow::kitap_islemleri);
    connect(ui->alma_label, &TiklanabilirLabel::clicked, this, &MainWindow::odunc_alma_islemleri);
    connect(ui->alma2_label, &TiklanabilirLabel::clicked, this, &MainWindow::odunc_alma_islemleri);
    connect(ui->teslim_label, &TiklanabilirLabel::clicked, this, &MainWindow::teslim_etme_islemleri);
    connect(ui->teslim2_label, &TiklanabilirLabel::clicked, this, &MainWindow::teslim_etme_islemleri);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::database_baglan() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_LOCATION);

    if (db.open())
        ui->statusbar->showMessage("Veritabanına Bağlanıldı!");
    else
        ui->statusbar->showMessage("Veritabanına Bağlanılamadı!");

    /*
    Database structure:
        uye:
        • uye_no (int)
        • uye_ad (text)
        • uye_soyad (text)

        kitap:
        • kitap_no (int)
        • kitap_ad (text)
        • kitap_sayisi (int)

        odunc_alinan:
        • uye_no (int)
        • kitap_no (int)
        • odunc_alma_tarihi(text)

        odunc_teslim_edilen:
        • uye_no (int)
        • kitap_no (int)
        • alma_tarihi(text)
        • verme_tarihi(text)
        • borc (int)
    */
}



void MainWindow::uye_islemleri() {
    UyeIslemleri* uye_i = new UyeIslemleri(this);
    uye_i->show();
}


void MainWindow::kitap_islemleri() {
    KitapIslemleri* kitap_i = new KitapIslemleri(this);
    kitap_i->show();
}


void MainWindow::odunc_alma_islemleri() {
    OduncAlma* odunc_a = new OduncAlma(this);
    odunc_a->show();
}


void MainWindow::teslim_etme_islemleri() {
    TeslimEtme* teslim_e = new TeslimEtme(this);
    teslim_e->show();
}

