#ifndef TESLIMETME_H
#define TESLIMETME_H

#include <QDialog>
#include <QSqlDatabase>

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

    void yenile();
};

#endif // TESLIMETME_H
