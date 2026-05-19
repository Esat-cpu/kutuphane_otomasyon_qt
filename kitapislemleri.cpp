#include "kitapislemleri.h"
#include "ui_kitapislemleri.h"

KitapIslemleri::KitapIslemleri(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KitapIslemleri)
{
    ui->setupUi(this);
}

KitapIslemleri::~KitapIslemleri()
{
    delete ui;
}
