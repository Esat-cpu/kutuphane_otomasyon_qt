#ifndef ODUNCALMA_H
#define ODUNCALMA_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class OduncAlma;
}

class OduncAlma : public QDialog
{
    Q_OBJECT

public:
    explicit OduncAlma(QWidget *parent = nullptr);
    ~OduncAlma();

private slots:
    void on_uye_table_clicked(const QModelIndex &index);

    void on_kitap_table_clicked(const QModelIndex &index);

    void on_oduncAl_button_clicked();

private:
    Ui::OduncAlma *ui;

    QSqlTableModel* uye_model;
    QSqlTableModel* kitap_model;
    QSqlTableModel* odunc_model;

    int secili_kitap_stok;

    void yenile();
};

#endif // ODUNCALMA_H
