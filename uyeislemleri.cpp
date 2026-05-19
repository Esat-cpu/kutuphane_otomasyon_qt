#include "uyeislemleri.h"
#include "ui_uyeislemleri.h"

UyeIslemleri::UyeIslemleri(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UyeIslemleri)
{
    ui->setupUi(this);
}

UyeIslemleri::~UyeIslemleri()
{
    delete ui;
}
