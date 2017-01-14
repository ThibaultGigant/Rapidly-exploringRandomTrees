#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent, CentralWidget *cw, QPointF* point, QString path) : QWidget(parent)
{
    this->point = point;
    this->cw = cw;

    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    setStyleSheet(path);
}


void DragWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (posOk(event->pos())){
            moving = true;
            //this->move(event->pos);
        }
    }
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && moving)
        if (posOk(event->pos())){
            //this->move(toScale(event->pos()));
            move(event->pos());
            qDebug() << mapToGlobal(parentWidget()->parentWidget()->geometry().topLeft());
        }
}


void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && moving) {
        if (posOk(event->pos())){
            //this->move(toScale(event->pos()));
            move(event->pos());
            qDebug() << mapToGlobal(parentWidget()->parentWidget()->geometry().topLeft());
            moving = false;
        }
    }
}

QPoint DragWidget::toScale(QPoint point){

    float ratioW = (float)(this->cw->WIDTH) / (float)(this->parentWidget()->parentWidget()->width());
    float ratioH = (float)(this->cw->HEIGHT) / (float)(this->parentWidget()->parentWidget()->height());

    QPoint res = QPoint((int)(point.x() * ratioW), (int)(point.y() * ratioH));
    qDebug() << "Sizes : " << parentWidget()->parentWidget()->width() << " " << parentWidget()->parentWidget()->height() ;
    qDebug() << "Ratios : " << ratioW << " " << ratioH << " Point in : " << point << "Point out : " << res;

    return res;
}

bool DragWidget::posOk(QPoint point){
    return point.x() >= 0 && point.x() < this->parentWidget()->width() && point.y() >= 0 && point.y() < this->parentWidget()->height();
}
