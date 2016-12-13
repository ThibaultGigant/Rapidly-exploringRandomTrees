#include "heightmapviewpanel.h"

HeightMapViewPanel::HeightMapViewPanel(QWidget *parent, Config *config) : QWidget(parent)
{

    this->config = config;
    this->config->setHeightMapViewPanel(this);
}




void QWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);
}


QPoint HeightMapFrame::toScreenPix(QPointF p){

    int x = this->width() / config->currentMap->getWidth();
    int y = this->height() / config->currentMap->getHeight();

    return new QPoint(x,y);
}

QPointF HeightMapFrame::toHeightMapPoint(QPoint p){

    qreal x = config->currentMap->getWidth() / this->width();
    qreal y = config->currentMap->getHeight() / this->height();

    return new QPointF(x,y);
}

void HeightMapFrame::drawLine(QPointF p1, QPointF p2){
    // We might need to store a vector of nodes and edges for this.
    // I think Qt wants us to redraw everything when updating the canvas
}


