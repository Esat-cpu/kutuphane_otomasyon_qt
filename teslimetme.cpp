#include "teslimetme.h"
#include "ui_teslimetme.h"

TeslimEtme::TeslimEtme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TeslimEtme)
{
    ui->setupUi(this);
}

TeslimEtme::~TeslimEtme()
{
    delete ui;
}
