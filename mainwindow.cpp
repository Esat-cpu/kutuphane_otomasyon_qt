#include "mainwindow.h"
#include "ui_mainwindow.h"

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

}


void MainWindow::kitap_islemleri() {

}


void MainWindow::odunc_alma_islemleri() {

}


void MainWindow::teslim_etme_islemleri() {

}

