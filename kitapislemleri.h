#ifndef KITAPISLEMLERI_H
#define KITAPISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class KitapIslemleri;
}

class KitapIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit KitapIslemleri(QWidget *parent = nullptr);
    ~KitapIslemleri();

private slots:
    void on_kitap_table_clicked(const QModelIndex &index);

    void on_yeniKayit_button_clicked();

    void on_guncelle_button_clicked();

    void on_sil_button_clicked();

private:
    Ui::KitapIslemleri *ui;

    QSqlTableModel* kitap_model;
    QSqlTableModel* odunc_model;
    QSqlTableModel* teslim_model;

    void yenile();
};

#endif // KITAPISLEMLERI_H
