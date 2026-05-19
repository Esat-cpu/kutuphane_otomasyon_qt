#ifndef TIKLANABILIRLABEL_H
#define TIKLANABILIRLABEL_H

#include <QLabel>
#include <QMouseEvent>

class TiklanabilirLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TiklanabilirLabel(QWidget *parent = nullptr);

signals:
    void clicked();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // TIKLANABILIRLABEL_H
