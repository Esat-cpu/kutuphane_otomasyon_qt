#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void uye_islemleri();
    void kitap_islemleri();
    void odunc_alma_islemleri();
    void teslim_etme_islemleri();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
