#include "heightmapviewpanel.h"

HeightMapViewPanel::HeightMapViewPanel(QWidget *parent, Config *config) : QWidget(parent)
{

    this->config = config;

    this->view = QImage(config->getCurrentMap()->getWidth(), config->getCurrentMap()->getHeight(), QImage::Format_ARGB32_Premultiplied);
    this->edgeBrush = QBrush(Qt::black);
    this->vertexBrush = QBrush(Qt::black);
    this->vertexCount = 0;
    this->scribbling = false;
    updateViewImage();

    connect(config, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(drawElement(Vertex*)));
}


void HeightMapViewPanel::updateViewImage(){
    int c;
    for (int i = 0; i < config->WIDTH; i++)
        for (int j = 0; j < config->HEIGHT; j++)
        {
            c = 255 - config->getCurrentMap()->getMap()[i][j];
            this->view.setPixelColor(i, j, QColor(c, c, c, 255));
        }
}


void HeightMapViewPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, view);
}


void HeightMapViewPanel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void HeightMapViewPanel::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void HeightMapViewPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}


void HeightMapViewPanel::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&this->view);
    painter.setBrush(vertexBrush);
    painter.drawLine(lastPoint, endPoint);

    int rad = (1 / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void HeightMapViewPanel::drawElement(Vertex *vertex)
{
    QPointF point1, point2;
    QPainter painter;

    painter.begin(&this->view);
    painter.setRenderHint(QPainter::Antialiasing);


    QColor red = QColor((int)(255.0 / 1000.0 * vertexCount),0,0,255);
    vertexBrush.setColor(red);
    painter.setBrush(vertexBrush);

    // Drawing the new Edge

    point1 = vertex->getPosition();
    point2 = vertex->getParent()->getPosition();

    painter.drawLine(point1, point2);

    //Drawing the new Vertex

    painter.drawEllipse(point1, 3, 3);

    // Finalize
    vertexCount++;
    painter.end();
    update();
}




/*
 *
 *
 *  USELESS ZONE
 *
 *
 */


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




