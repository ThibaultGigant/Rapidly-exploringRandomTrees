#include "threadgenerator.h"
#include <algorithm>

/**
 * @brief Constructor
 * @param cw Central Widget, used to connect the simulation and the display
 * @param configs List of configurations to run
 */
ThreadGenerator::ThreadGenerator(CentralWidget *cw, QVector<Config *> configs)
{
    this->configs = configs;
    this->cw = cw;
    this->stopSimulations = false;

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
            emit emitClearImage(expectedNbVertices);

            // Launching simulation
            session = new Session(config);
            //connect(this, SIGNAL(emitStop()), session, SLOT(stop()));
            config->getGenerator()->setSession(session);
            vertex = session->generate();

            // Verification if the display is over before continue
            while (vertex != lastVertexDrawn)
            {
                QThread::msleep(1);
            }

            // Disconnection of current session
            //disconnect(this, SIGNAL(emitStop()), session, SLOT(stop()));

            delete session;
        }

        // Disconnecting the current config to the central widget
        disconnect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));

    }

    emit emitDone();
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
    qDebug() << "skip signal received";
    this->session->stop();
    //emit emitStop();
}

/**
 * @brief Stops all simulations
 */
void ThreadGenerator::stop()
{
    qDebug() << "stop signal received in thread";
    this->stopSimulations = true;
    this->session->stop();
    //emit emitStop();
}
