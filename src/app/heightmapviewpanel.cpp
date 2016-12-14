#include "heightmapviewpanel.h"

HeightMapViewPanel::HeightMapViewPanel(QWidget *parent, Config *config) : QWidget(parent)
{

    int c;
    this->config = config;
    //this->config->setHeightMapViewPanel(this);

    this->view = QImage(config->getCurrentMap()->getWidth(), config->getCurrentMap()->getHeight(), QImage::Format_ARGB32_Premultiplied);

    for (int i = 0; i < config->WIDTH; i++)
        for (int j = 0; j < config->HEIGHT; j++)
        {
            c = 255 - config->getCurrentMap()->getMap()[i][j];
            this->view.setPixelColor(i, j, QColor(c, c, c, 255));
        }
    connect(config, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(drawElement(Vertex*)));
}




void HeightMapViewPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, view);
}


QPoint HeightMapViewPanel::toScreenPix(QPointF p){

    int x = p.x() * this->width() / config->getCurrentMap()->getWidth();
    int y = p.y() * this->height() / config->getCurrentMap()->getHeight();

    return QPoint(x,y);
}

QPoint HeightMapViewPanel::toScreenPix(QPoint p){

    int x = p.x() * 600 / config->getCurrentMap()->getWidth();
    int y = p.y() * 400 / config->getCurrentMap()->getHeight();

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
    painter.drawEllipse(point1, 2, 2);

    painter.end();
    this->view.setPixelColor(200, 200, QColor(255, 0, 0, 255));
    update();
}
