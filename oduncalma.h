#ifndef ODUNCALMA_H
#define ODUNCALMA_H

#include <QDialog>

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
};

#endif // ODUNCALMA_H
