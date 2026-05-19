#ifndef UYEISLEMLERI_H
#define UYEISLEMLERI_H

#include <QDialog>

namespace Ui {
class UyeIslemleri;
}

class UyeIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit UyeIslemleri(QWidget *parent = nullptr);
    ~UyeIslemleri();

private:
    Ui::UyeIslemleri *ui;
};

#endif // UYEISLEMLERI_H
