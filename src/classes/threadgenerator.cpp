#include "threadgenerator.h"
#include <algorithm>

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
    this->savedMaps = QVector();


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

        if (!saveConfig()){
            qDebug() << "Config Directory Creation Failed";
        }

        // Launching the correct number of simulations
        for (int i = 0; i < config->getNbRuns(); i++)
        {
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
    if(!QDir::mkdir(dir)){
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

    QString name = "HeightMap"+(savedMaps.length()+1);
    map->setName(name);

    QFile file(dir +"/"+name+".cnf");
    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }

    QTextStream out(&file);
    out << map->toFileString();
    file.close();
    return true;
}

bool saveRunFile(Session *session){

    QFile file(dirPath+"/Config_"+configCount+"/runFile"+runCount+".run");
    if (!file.open(QIODevice::ReadWrite)){
        return false;
    }

    QTextStream out(&file);
    out << session->getEnvironment()->toString();
    file.close();

    //Save QImage and surface covered

    return true;
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
