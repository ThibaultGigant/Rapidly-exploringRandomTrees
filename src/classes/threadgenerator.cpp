#include "threadgenerator.h"
#include <algorithm>
#include "src/classes/environment/environment.h"

/**
 * @brief Constructor
 * @param cw Central Widget, used to connect the simulation and the display
 * @param configs List of configurations to run
 * @param dirPath Relative or absolute link to the directory where the results will be stored
 */
ThreadGenerator::ThreadGenerator(CentralWidget *cw, QVector<Config *> configs, QString dirPath)
{
    this->configs = configs;
    this->cw = cw;
    this->stopSimulations = false;
    this->dirPath = dirPath;
    save = dirPath != "";
    configCount = 0;
    runCount = 0;
    this->savedMaps = QVector<HeightMap*>();


    connect(this, SIGNAL(emitClearImage(int)), this->cw, SLOT(receiveClearImage(int)));
    connect(this, SIGNAL(emitDone()), this->cw, SLOT(done()));
}

/**
 * @brief Launches the simulations
 */
void ThreadGenerator::run()
{
    Config *config;
    Vertex *vertex;
    int expectedNbVertices;



    // Launching simulations for each config
    foreach (config, this->configs) {
        if (this->stopSimulations)
            break;

        // Connecting the current config to the central widget
        connect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));

        if (!saveConfig(config)){
            qDebug() << "Config Directory Creation Failed";
        }

        // Launching the correct number of simulations
        for (int i = 0; i < config->getNbRuns(); i++)
        {
            Vertex::resetVertexId();

            if (this->stopSimulations)
                break;

            config->reset();
            this->cw->setCurrentMap(config->getCurrentMap());

            // Clear the display
            if (config->getEndMethod()->getMaxNumber() > 0 && config->getEndMethod()->getLimitTime() > 0)
                expectedNbVertices = std::min((int) config->getEndMethod()->getMaxNumber(), (int) config->getEndMethod()->getLimitTime() * 1000 / std::max(config->getSleepTime(), 1));
            else if (config->getEndMethod()->getMaxNumber() > 0)
                expectedNbVertices = config->getEndMethod()->getMaxNumber();
            else
                expectedNbVertices = config->getEndMethod()->getLimitTime() * 1000 / std::max(config->getSleepTime(), 1);
            //qDebug() << expectedNbVertices;
            emit emitClearImage(expectedNbVertices);

            // Launching simulation
            session = new Session(config);
            //connect(this, SIGNAL(emitStop()), session, SLOT(stop()));
            config->getGenerator()->setSession(session);
            vertex = session->generate();


            saveRunFile(session);

            // Verification if the display is over before continue
            while (vertex != lastVertexDrawn)
            {
                QThread::msleep(1);
            }

            // Disconnection of current session
            //disconnect(this, SIGNAL(emitStop()), session, SLOT(stop()));
            runCount++;
            delete session;
        }

        // Disconnecting the current config to the central widget
        disconnect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));
        configCount++;
    }

    emit emitDone();
}


bool ThreadGenerator::saveConfig(Config * conf){

    if (!save) return true;

    QString dir = dirPath+"/Config_"+QString::number(configCount);
    QDir d = QDir(dir);

    if(!d.mkdir(dir)){
        return false;
    }

    if(!saveHeightMap(conf->getCurrentMap())){
        return false;
    }

    QFile file(dir +"/conf"+QString::number(configCount)+".txt");

    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }
    QTextStream out(&file);
    out << conf->toString();
    file.close();
    return true;
}

bool ThreadGenerator::saveHeightMap(HeightMap *map){
    if(savedMaps.contains(map)){
        return true;
    }

    QString name = "HeightMap"+QString::number((savedMaps.length()+1));
    map->setName(name);

    QFile file(dirPath +"/"+name+".hmf");
    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }

    QTextStream out(&file);
    out << map->toFileString();
    file.close();
    return true;
}

bool ThreadGenerator::saveRunFile(Session *session){

    QFile file(dirPath+"/Config_"+QString::number(configCount)+"/runFile"+QString::number(runCount)+".txt");
    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }

    QString path = dirPath+"/Config_"+QString::number(configCount)+"/";
    bool success = generateAndSaveResultImage(session->getEnvironment()->getVertices(), session->getDeltaT()/2, session->getMap(), path);

    QTextStream out(&file);
    out << QString::number(surfaceRatio)+"\n";
    out << QString::number(surfaceRatioConnected)+"\n";
    out << session->getEnvironment()->toString();
    file.close();

    return success;
}

bool ThreadGenerator::generateAndSaveResultImage(QVector<Vertex*> vertices, float influence, HeightMap *map, QString path){

    int w, h, count, c, i;
    unsigned char *data, *dataInflu,*dataInfluConnected;
    QImage view, viewInflu, viewInfluConnected;

    QPointF point1;
    QColor blue;


    QVector<QPair<QPainterPath,QColor>> vectPathVertices;
    QVector<QPainterPath> vectPathInfuence;

    QVector<QPainterPath> vectPathInfuenceConnected;

    QPainterPath pathInfluenceZone;
    QPainterPath pathInfluenceZoneConnected;
    QPainterPath pathEdgeVertices;

    QBrush brush;
    QPen pen;

    Vertex *v;

    w = map->getWidth();
    h = map->getHeight();
    data = new unsigned char[4 * w * h ];
    view = QImage(data, w, h, QImage::Format_RGB32);

    dataInflu = new unsigned char[4 * w * h ];
    viewInflu = QImage(dataInflu, w, h, QImage::Format_RGB32);

    dataInfluConnected = new unsigned char[4 * w * h ];
    viewInfluConnected = QImage(dataInfluConnected, w, h, QImage::Format_RGB32);

    pathInfluenceZone = QPainterPath(QPointF(0,0));
    pathInfluenceZoneConnected = QPainterPath(QPointF(0,0));

    count = vertices.length();

    Vertex *marker = vertices[0]->getConnectedComponentPointer();

    for(i = 0;i < count; i++){

        v = vertices[i];
        point1 = v->getPosition();

        // Ellipse
        pathEdgeVertices = QPainterPath(point1);
        c = 200.0/count*i;
        blue = QColor(0,c,0,255);
        pathEdgeVertices.addEllipse(point1,5,5);
        vectPathVertices.append(QPair<QPainterPath,QColor>(pathEdgeVertices,blue));

        // Influence Zone

        pathInfluenceZone = QPainterPath();
        pathInfluenceZone.addEllipse(point1, influence, influence);
        vectPathInfuence.append(pathInfluenceZone);

        if(v->getConnectedComponentPointer()==marker){
            vectPathInfuenceConnected.append(pathInfluenceZone);
        }

        //Edges
        foreach (Vertex *tempVertex, v->getChildren()) {
            pathEdgeVertices = QPainterPath(point1);
            pathEdgeVertices.lineTo(tempVertex->getPosition());
            vectPathVertices.append(QPair<QPainterPath,QColor>(pathEdgeVertices,blue));
            //TODO:draw path in influenceZone

            // Influence Zone
            pathInfluenceZone = QPainterPath(point1);
            pathInfluenceZone.lineTo(tempVertex->getPosition());
            vectPathInfuence.append(pathInfluenceZone);

            if(v->getConnectedComponentPointer()==marker){
                pathInfluenceZoneConnected = QPainterPath(point1);
                pathInfluenceZoneConnected.lineTo(tempVertex->getPosition());
                vectPathInfuenceConnected.append(pathInfluenceZone);

            }

        }
    }

    //count = vertices.length();


    QPainter painter(&view);

    QPainter painterInflu(&viewInflu);

    QPainter painterInfluConnected(&viewInfluConnected);

    painter.setRenderHint(QPainter::Antialiasing);
    blue = QColor(60,60,220,255);
    brush = QBrush(blue);
    pen = QPen(blue);
    pen.setBrush(brush);
    pen.setWidthF(influence);
    painterInflu.setBrush(brush);
    painterInflu.setPen(pen);
    painterInfluConnected.setBrush(brush);
    painterInfluConnected.setPen(pen);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.fillRect(view.rect(),Qt::white);
    painterInflu.fillRect(viewInflu.rect(),Qt::white);
    painterInfluConnected.fillRect(viewInfluConnected.rect(),Qt::white);


    foreach(pathInfluenceZone, vectPathInfuence){
        painter.drawPath(pathInfluenceZone);
        painterInflu.drawPath(pathInfluenceZone);
    }

    foreach(pathInfluenceZoneConnected, vectPathInfuenceConnected){
        painterInfluConnected.drawPath(pathInfluenceZoneConnected);
    }


    for(i = 0;i < vectPathVertices.length(); i++){

        pathEdgeVertices = vectPathVertices[i].first;
        brush = QBrush(vectPathVertices[i].second);
        pen = QPen(vectPathVertices[i].second);
        pen.setWidth(2);
        painter.setBrush(brush);
        painter.setPen(pen);

        painter.drawPath(pathEdgeVertices);
    }


    drawHeightMap(map,data);


    //Surface Ratio Calculation

    float totalSize = w*h;
    float covered = 0;
    float coveredConnected = 0;

    for (int x = 0; x < w; x++){
        for(int y = 0; y < h;y++){
            if(viewInflu.pixelColor(x,y).red() < 70){
                covered ++;
            }
            if(viewInfluConnected.pixelColor(x,y).red() < 70){
                coveredConnected ++;
            }
        }
    }

    surfaceRatio = 100.0 * covered / totalSize;
    surfaceRatioConnected = 100.0 * coveredConnected / totalSize;

    bool success  = view.save(path+"view"+QString::number(runCount)+".png");
    success = success && viewInflu.save(path+"viewInflu"+QString::number(runCount)+".png");
    success = success && viewInfluConnected.save(path+"viewConnected"+QString::number(runCount)+".png");

    return success;

}

void ThreadGenerator::drawHeightMap(HeightMap *hmap, unsigned char *data){

    unsigned char c;

    int w = hmap->getWidth(), h = hmap->getHeight();

    QVector<QVector<int> > map = hmap->getMap();

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


/**
 * @brief Receives the last vertex drawn in the HeightMapViewPanel
 * @param v Last vertex drawn
 */
void ThreadGenerator::getVertexDrawn(Vertex *v)
{
    this->lastVertexDrawn = v;
}

/**
 * @brief Stops the current simulation to start directly the next one
 */
void ThreadGenerator::skipToNext()
{
    //qDebug() << "skip signal received";
    this->session->stop();
    //emit emitStop();
}

/**
 * @brief Stops all simulations
 */
void ThreadGenerator::stop()
{
    //qDebug() << "stop signal received in thread";
    this->stopSimulations = true;
    this->session->stop();
    //emit emitStop();
}


