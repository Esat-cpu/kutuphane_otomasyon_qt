#ifndef KITAPISLEMLERI_H
#define KITAPISLEMLERI_H

#include <QDialog>

namespace Ui {
class KitapIslemleri;
}

class KitapIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit KitapIslemleri(QWidget *parent = nullptr);
    ~KitapIslemleri();

private:
    Ui::KitapIslemleri *ui;
};

#endif // KITAPISLEMLERI_H
