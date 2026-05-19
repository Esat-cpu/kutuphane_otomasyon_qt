#ifndef TESLIMETME_H
#define TESLIMETME_H

#include <QDialog>

namespace Ui {
class TeslimEtme;
}

class TeslimEtme : public QDialog
{
    Q_OBJECT

public:
    explicit TeslimEtme(QWidget *parent = nullptr);
    ~TeslimEtme();

private:
    Ui::TeslimEtme *ui;
};

#endif // TESLIMETME_H
