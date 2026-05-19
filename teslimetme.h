#ifndef TESLIMETME_H
#define TESLIMETME_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class TeslimEtme;
}

class TeslimEtme : public QDialog
{
    Q_OBJECT

public:
    explicit TeslimEtme(QWidget *parent = nullptr);
    ~TeslimEtme();

private slots:
    void on_odunc_table_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::TeslimEtme *ui;

    QSqlTableModel* odunc_model;
    QSqlTableModel* teslim_model;

    QString secili_kayit_tarih;

    void yenile();
};

#endif // TESLIMETME_H
