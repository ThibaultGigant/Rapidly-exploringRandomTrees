#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent, QPointF* point, QColor color) : QWidget(parent)
{
    this->point = point;

    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

}


void DragWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (posOk(event->pos())){
            moving = true;
            this->move(event->pos());
        }
    }
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && moving)
        if (posOk(event->pos())){
            this->move(event->pos());
        }
}

void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && moving) {
        if (posOk(event->pos())){
            this->move(event->pos());
            moving = false;
        }
    }
}

bool DragWidget::posOk(QPoint point){
    return point.x() >= 0 && point.x() < this->parentWidget()->width() && point.y() >= 0 && point.y() < this->parentWidget()->height();
}
