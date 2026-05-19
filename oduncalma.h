#ifndef ODUNCALMA_H
#define ODUNCALMA_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class OduncAlma;
}

class OduncAlma : public QDialog
{
    Q_OBJECT

public:
    explicit OduncAlma(QWidget *parent = nullptr);
    ~OduncAlma();

private:
    Ui::OduncAlma *ui;

    void yenile();
};

#endif // ODUNCALMA_H
