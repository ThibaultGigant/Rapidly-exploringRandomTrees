#include "heightmapviewpanel.h"

HeightMapViewPanel::HeightMapViewPanel(QWidget *parent, Config *config) : QWidget(parent)
{

    this->config = config;
    this->vertexList = QVector<Vertex*>();
    this->drawingAllowed = true;

    //Image stuff
    this->view = QImage(config->getCurrentMap()->getWidth(), config->getCurrentMap()->getHeight(), QImage::Format_ARGB32_Premultiplied);
    setupPens();
    updateImage();
    this->scribbling = false;

    //Connexions
    connect(config, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(addElement(Vertex*)));
}

void HeightMapViewPanel::setupPens(){
    this->edgePen = QPen();
    this->hmPen = QPen();
    this->brush = QBrush(Qt::black);
    this->hmPen.setWidth(2);
    this->edgePen.setWidth(2);
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//                                MOUSE EVENTS
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void HeightMapViewPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, view);
}


void HeightMapViewPanel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawingAllowed) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void HeightMapViewPanel::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling && drawingAllowed)
        drawLineTo(event->pos());
}

void HeightMapViewPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && drawingAllowed) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//                                   DRAWING
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void HeightMapViewPanel::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&this->view);
    painter.setBrush(brush);
    painter.setPen(hmPen);
    painter.drawLine(lastPoint, endPoint);

    int rad = (hmPen.width() / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ UPDATE IMAGE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void HeightMapViewPanel::updateImage()
{

    QPainter painter(&this->view);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush);

    brush.setColor(Qt::black);
    edgePen.setColor(Qt::black);

    view.fill(QColor(Qt::white));

    drawHeightMap();

    drawVertices(painter);

    // Finalize
    update();
}

void HeightMapViewPanel::drawVertices(QPainter painter){

    QPointF point1, point2;
    painter.setPen(edgePen);

    for (int i = 0;i < vertexList.size();i++){
        Vertex *vertex = vertexList[i];
        QColor red = QColor((int)(255.0 / vertexList.size() * i),0,0,255);

        brush.setColor(red);
        edgePen.setColor(red);

        point1 = vertex->getPosition();
        point2 = vertex->getParent()->getPosition();

        painter.drawLine(point1, point2);
        painter.drawEllipse(point1, 3, 3);
    }
}

void HeightMapViewPanel::drawHeightMap(){

    int c;
    for (int i = 0; i < config->WIDTH; i++)
        for (int j = 0; j < config->HEIGHT; j++)
        {
            c = 255 - config->getCurrentMap()->getMap()[i][j];
            this->view.setPixelColor(i, j, QColor(c, c, c, 255));
        }
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SAVE HEIGHT MAP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void HeightMapViewPanel::drawImageOnHeightMap(){
    for (int i = 0; i< config->WIDTH;i++){
        for (int j = 0; j< config->HEIGHT;j++){
            QColor c = view.pixelColor(i,j);
            int pix = c.red() + c.blue() + c.green();
            config->getCurrentMap()->getMap()[i][j] = (pix > 0)?255:0;
        }
    }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//                                   SIGNALS
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



void HeightMapViewPanel::addElement(Vertex *vertex){
    vertexList.append(vertex);
}

void HeightMapViewPanel::clear(bool doUpdateImage){
    vertexList.clear();
    if (doUpdateImage) updateImage();
}

void HeightMapViewPanel::setDrawPermission(bool isDrawingAllowed)
{
    this->drawingAllowed = isDrawingAllowed;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//                               USELESS ZONE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


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




