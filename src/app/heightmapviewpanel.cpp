#include "heightmapviewpanel.h"

HeightMapViewPanel::HeightMapViewPanel(QWidget *parent, Config *config) : QWidget(parent)
{

    this->config = config;
    //this->config->setHeightMapViewPanel(this);

    uchar content[config->WIDTH * config->HEIGHT];
    for (int i = 0; i < config->WIDTH * config->HEIGHT; i++)
        content[i] = 0;

    this->view = QImage(content, config->WIDTH, config->HEIGHT, QImage::Format_ARGB32_Premultiplied);

    connect(config, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(drawElement(Vertex*)));
}




void HeightMapViewPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);

    painter.drawImage(0, 0, view);
}


QPoint HeightMapViewPanel::toScreenPix(QPointF p){

    int x = p.x() * this->width() / config->getCurrentMap()->getWidth();
    int y = p.y() * this->height() / config->getCurrentMap()->getHeight();

    return QPoint(x,y);
}

QPointF HeightMapViewPanel::toHeightMapPoint(QPoint p){

    qreal x = p.x() * config->getCurrentMap()->getWidth() / this->width();
    qreal y = p.y() * config->getCurrentMap()->getHeight() / this->height();

    return QPointF(x,y);
}

void HeightMapViewPanel::drawElement(Vertex *vertex)
{
    QPointF point1, point2;
    QPainter painter;

    painter.begin(&this->view);

    point1 = vertex->getPosition();
    point2 = vertex->getParent()->getPosition();
    painter.drawLine(point1, point2);
    painter.drawEllipse(point1, 5, 5);

    painter.end();
}
