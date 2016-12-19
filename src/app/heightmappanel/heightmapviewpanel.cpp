#include "heightmapviewpanel.h"
#include "src/app/centralwidget.h"

HeightMapViewPanel::HeightMapViewPanel(CentralWidget *centralWidget, QWidget *parent) :
    QWidget(parent)
{
    // Variables initialization
    this->centralWidget = centralWidget;
    this->vertexList = QVector<Vertex*>();
    this->drawingAllowed = true;

    //Image stuff
    this->view = QImage(this->centralWidget->getCurrentMap()->getWidth(),
                        this->centralWidget->getCurrentMap()->getHeight(),
                        QImage::Format_ARGB32_Premultiplied);
    setupPens();
    updateImage();
    this->scribbling = false;

    //Connexions
    connect(this->centralWidget, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(addElement(Vertex*)));
    connect(this->centralWidget, SIGNAL(emitUpdateImage()), this, SLOT(updateImage()));
    connect(this->centralWidget, SIGNAL(clearImage(int)), this, SLOT(clear(int)));
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
    if (event->isAccepted())
    {
        QPainter painter(this);
        painter.drawImage(0, 0, view);
    }
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
    brush.setColor(Qt::black);
    edgePen.setColor(Qt::black);
    view.fill(QColor(Qt::white));
    drawHeightMap();
    drawVertices();
    update();
}

void HeightMapViewPanel::drawVertices(){

    QPainter painter(&this->view);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush);

    QPointF point1, point2;
    painter.setPen(edgePen);

    for (int i = 0;i < vertexList.size();i++){
        Vertex *vertex = vertexList[i];
        QColor red = QColor((int)(255.0 / vertexList.size() * i),0,0,255);
        qDebug() << red;
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
    for (int i = 0; i < this->centralWidget->getCurrentMap()->getWidth(); i++)
        for (int j = 0; j < this->centralWidget->getCurrentMap()->getHeight(); j++)
        {

        }


}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SAVE HEIGHT MAP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void HeightMapViewPanel::drawImageOnHeightMap(){
    for (int i = 0; i< this->centralWidget->getCurrentMap()->getWidth();i++){
        for (int j = 0; j< this->centralWidget->getCurrentMap()->getHeight();j++){
            QColor c = view.pixelColor(i,j);
            int pix = c.red() + c.blue() + c.green();
            this->centralWidget->getCurrentMap()->getMap()[i][j] = (pix > 0)?255:0;
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

    QPainter painter(&this->view);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush);

    QPointF point1, point2;
    painter.setPen(edgePen);

//    QColor red = QColor((int)(255.0 / vertexList.size() * i),0,0,255);
//    qDebug() << red;
//    brush.setColor(red);
//    edgePen.setColor(red);

    point1 = vertex->getPosition();
    point2 = vertex->getParent()->getPosition();

    painter.drawLine(point1, point2);
    painter.drawEllipse(point1, 3, 3);

    int rad = 5;
    update(QRect(point1.toPoint(), point2.toPoint()).normalized().adjusted(-rad, -rad, +rad, +rad));

}

void HeightMapViewPanel::clear(int count){
    vertexList.clear();
    view.fill(QColor(Qt::white));
    drawHeightMap();
    update();
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

    int x = p.x() * this->width() / this->centralWidget->getCurrentMap()->getWidth();
    int y = p.y() * this->height() / this->centralWidget->getCurrentMap()->getHeight();

    return QPoint(x,y);
}

QPoint HeightMapViewPanel::toScreenPix(QPoint p){

    int x = p.x() * 600 / this->centralWidget->getCurrentMap()->getWidth();
    int y = p.y() * 400 / this->centralWidget->getCurrentMap()->getHeight();

    return QPoint(x,y);
}

QPointF HeightMapViewPanel::toHeightMapPoint(QPoint p){

    qreal x = p.x() * this->centralWidget->getCurrentMap()->getWidth() / this->width();
    qreal y = p.y() * this->centralWidget->getCurrentMap()->getHeight() / this->height();

    return QPointF(x,y);
}




