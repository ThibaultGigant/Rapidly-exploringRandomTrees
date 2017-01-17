#include "threadgenerator.h"
#include <algorithm>
#include "src/classes/environment/environment.h"

/**
 * @brief Constructor
 * @param cw Central Widget, used to connect the simulation and the display
 * @param configs List of configurations to run
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

    QString dir = dirPath+"/Config_"+configCount;
    QDir d;
    if(!d.mkdir(dir)){
        return false;
    }

    if(!saveHeightMap(conf->getCurrentMap())){
        return false;
    }

    QFile file(dir +"/conf"+configCount+".cnf");

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

    QFile file(dirPath +"/"+name+".cnf");
    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }

    QTextStream out(&file);
    out << map->toFileString();
    file.close();
    return true;
}

bool ThreadGenerator::saveRunFile(Session *session){

    QFile file(dirPath+"/Config_"+QString::number(configCount)+"/runFile"+QString::number(runCount)+".run");
    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }

    QTextStream out(&file);
    out << session->getEnvironment()->toString();
    file.close();

    QString path = dirPath+"/Config_"+QString::number(configCount)+"/imageResult"+QString::number(runCount)+".png";

    return generateAndSaveResultImage(session->getEnvironment()->getVertices(), session->getDeltaT()/2, session->getMap(), path);
}

bool ThreadGenerator::generateAndSaveResultImage(QVector<Vertex*> vertices, float influence, HeightMap *map, QString path){

    int w, h, count, c, i;
    unsigned char *data;
    QImage view;

    QPointF point1;
    QColor blue;


    QVector<QPainterPath> pathVertices;

    QPainterPath pathInfluenceZone;
    QPainterPath pathEdgeVertices;

    QBrush brush;
    QPen pen;

    Vertex *v;

    w = map->getWidth();
    h = map->getHeight();
    data = new unsigned char[4 * w * h ];
    view = QImage(data, w, h, QImage::Format_RGB32);

    pathInfluenceZone = QPainterPath(QPointF(0,0));

    for(i = 0;i < vertices.length(); i++){

        v = vertices[i];
        point1 = v->getPosition();

        pathEdgeVertices = QPainterPath(point1);

        pathEdgeVertices.addEllipse(point1,5,5);

        pathInfluenceZone.addEllipse(point1, influence, influence);

        foreach (Vertex *tempVertex, v->getChildren()) {
            pathEdgeVertices.lineTo(tempVertex->getPosition());
            //TODO:draw path in influenceZone
        }

        pathVertices.append(pathEdgeVertices);
    }

    count = vertices.length();


    QPainter painter(&view);
    painter.setRenderHint(QPainter::Antialiasing);
    blue = QColor(60,60,220,255);
    brush = QBrush(blue);
    pen = QPen(blue);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawPath(pathInfluenceZone);

    for(i = 0;i < vertices.length(); i++){
        pathEdgeVertices = pathVertices[i];
        c = 200.0/count*i;

        blue = QColor(0,c,0,255);
        brush = QBrush(blue);
        pen = QPen(blue);
        painter.setBrush(brush);
        painter.setPen(pen);

        painter.drawPath(pathEdgeVertices);
    }

    drawHeightMap(map,data);

    return view.save(path);

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


