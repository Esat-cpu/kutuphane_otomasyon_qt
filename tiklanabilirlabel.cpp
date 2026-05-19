#include "tiklanabilirlabel.h"

TiklanabilirLabel::TiklanabilirLabel(QWidget *parent)
    : QLabel(parent) {}


void TiklanabilirLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
    QLabel::mousePressEvent(event);
}
