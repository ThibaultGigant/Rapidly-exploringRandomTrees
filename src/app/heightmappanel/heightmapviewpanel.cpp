#include "heightmapviewpanel.h"
#include "src/app/centralwidget.h"
#include "src/classes/threadgenerator.h"


HeightMapViewPanel::HeightMapViewPanel(CentralWidget *centralWidget, QWidget *parent) :
    QWidget(parent)
{
    // Variables initialization
    this->centralWidget = centralWidget;
    this->vertexList = QVector<Vertex*>();
    this->modifAllowed = true;

    this->start = new DragWidget(this,centralWidget, centralWidget->getCurrentMap()->getStart(),"ressources/start.png");
    this->end = new DragWidget(this,centralWidget,centralWidget->getCurrentMap()->getStart(), "ressources/end.jpg");


    //Image stuff
    setupPens();
    setupImage();
    clear(0);
    this->scribbling = false;
    this->erase = false;

    //Connexions
    connect(this->centralWidget, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(addElement(Vertex*)));
    connect(this->centralWidget, SIGNAL(clearImage(int)), this, SLOT(clear(int)));
    connect(this->centralWidget,SIGNAL(emitModifAllowed(bool)),this,SLOT(setModifPermission(bool)));
}


void HeightMapViewPanel::setupPens(){
    this->penSize = 10;
    this->edgePen = QPen();
    this->hmPen = QPen();
    this->brush = QBrush(Qt::black);
    this->hmPen.setWidth(penSize);
    this->edgePen.setWidth(penSize);
}

void HeightMapViewPanel::setupImage(){

    this->w = this->centralWidget->getCurrentMap()->getWidth();
    this->h = this->centralWidget->getCurrentMap()->getHeight();

    data = new unsigned char[4 * w * h ];

    this->view = QImage(this->data, w, h, QImage::Format_RGB32);
    view.fill(Qt::white);
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
    if (event->button() == Qt::LeftButton && modifAllowed) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void HeightMapViewPanel::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling && modifAllowed)
        drawLineTo(event->pos());
}

void HeightMapViewPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && modifAllowed) {
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
    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor((erase)?Qt::white:Qt::black);
    hmPen.setColor((erase)?Qt::white:Qt::black);

    painter.setBrush(brush);
    painter.setPen(hmPen);
    painter.drawLine(lastPoint, endPoint);

    int rad = (hmPen.width() / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
    painter.end();
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ UPDATE IMAGE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



void HeightMapViewPanel::drawHeightMap(){

    unsigned char c;

    QVector<QVector<int> > map = this->centralWidget->getCurrentMap()->getMap();

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            c = (map[j][i] == 0)?255:0;
            if(c!=255){
                data[4 * (i * w + j)    ] = c;
                data[4 * (i * w + j) + 1] = c;
                data[4 * (i * w + j) + 2] = c;
                data[4 * (i * w + j) + 3] = 255;
            }
        }
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SAVE HEIGHT MAP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void HeightMapViewPanel::drawImageOnHeightMap(){
    QVector<QVector<int> > map = this->centralWidget->getCurrentMap()->getMap();
    for (int i = 0; i< w;i++){
        for (int j = 0; j< h;j++){
            QColor c = view.pixelColor(i,j);
            int pix = c.red()+c.blue()+c.green();//data[i*w + j] + data[i*w + j + 1] + data[i*w + j + 2];
            map[i][j] = (pix > 0)?0:255;
        }
    }

    this->centralWidget->getCurrentMap()->setMap(map);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//                                   SLOTS
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



void HeightMapViewPanel::addElement(Vertex *vertex){
    Vertex *tempVertex;
    vertexList.append(vertex);
    float maxDistance = 5, tempDistance;
    int r = 0;

    QPainter painter(&this->view);

    painter.setRenderHint(QPainter::Antialiasing);


    QPointF point1, point2;

    if(vertexList.size()==1){
        r = 255;
    }
    int g = 1 + 200.0 / count  *  vertexList.size(); //( 1.0 + (count * ));

    QColor red = QColor(r,g,0,255);

    //qDebug() << "Count : " << count << "Vertex size : " << vertexList.size() << " Green Value : " << red.green() << " R : " << r;

    brush.setColor(red);
    edgePen.setColor(red);
    edgePen.setWidth(2);
    painter.setPen(edgePen);
    painter.setBrush(brush);

    point1 = vertex->getPosition();

    // Adding a line between the vertex and it's parent
    if (vertex->getParent() != NULL)
    {
        point2 = vertex->getParent()->getPosition();
        painter.drawLine(point1, point2);
        maxDistance = QPointF::dotProduct(point1, point2);
    }

    // Adding a line between the vertex and all of its children
    foreach (tempVertex, vertex->getChildren()) {
        painter.drawLine(point1, tempVertex->getPosition());
        tempDistance = QPointF::dotProduct(point1, tempVertex->getPosition());
        if (tempDistance < maxDistance)
            maxDistance = tempDistance;
    }

    painter.drawEllipse(point1, 3, 3);

    int rad = 5;
    int tampon = (int) ceil(sqrt(maxDistance));
    point2 = QPointF(point1.x() + tampon, point1.y() + tampon);
    point1 = QPointF(point1.x() - tampon, point1.y() - tampon);

    update(QRect(point1.toPoint(), point2.toPoint()).normalized().adjusted(-rad, -rad, +rad, +rad));
    //update();
    edgePen.setWidth(penSize); // WHY I HAVE TO DO THIS ?! I USED TWO PENS !!!

    emit lastVertexDrawn(vertex);
}

void HeightMapViewPanel::clear(int count){
    this->count = count;
    vertexList.clear();
    view.fill(Qt::white);
    drawHeightMap();
    update();
}

void HeightMapViewPanel::setModifPermission(bool isModifAllowed)
{
    this->modifAllowed = isModifAllowed;
    emit sendModifAllowed(isModifAllowed);
}

void HeightMapViewPanel::increasePenSize(){
    penSize = std::min(MAX_SIZE,penSize+1);
    hmPen.setWidth(penSize);
    emit sendPenSize(penSize);
}

void HeightMapViewPanel::decreasePenSize(){
    penSize = std::max(MIN_SIZE,penSize-1);
    hmPen.setWidth(penSize);
    emit sendPenSize(penSize);
}

void HeightMapViewPanel::toggleMode(){
    erase = !erase;
}



//@@@@@@@@@@@@@@@@@@@@@ GET / SET @@@@@@@@@@@@@@@@@@@@@@@@@@@

int HeightMapViewPanel::getPenSize(){
    return penSize;
}

QImage HeightMapViewPanel::getView(){
    return view;
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




