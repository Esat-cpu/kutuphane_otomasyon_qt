#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uyeislemleri.h"
#include "kitapislemleri.h"
#include "oduncalma.h"
#include "teslimetme.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

