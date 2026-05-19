#ifndef UYEISLEMLERI_H
#define UYEISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class UyeIslemleri;
}

class UyeIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit UyeIslemleri(QWidget *parent = nullptr);
    ~UyeIslemleri();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_yeniKayit_button_clicked();

    void on_guncelle_button_clicked();

    void on_sil_button_clicked();

private:
    Ui::UyeIslemleri *ui;
    QSqlTableModel* model;

    void yenile();
};

#endif // UYEISLEMLERI_H
