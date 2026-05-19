#include "oduncalma.h"
#include "ui_oduncalma.h"

OduncAlma::OduncAlma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OduncAlma)
{
    ui->setupUi(this);
}

OduncAlma::~OduncAlma()
{
    delete ui;
}
