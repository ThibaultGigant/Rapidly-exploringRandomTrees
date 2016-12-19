#include "threadgenerator.h"
#include <algorithm>

ThreadGenerator::ThreadGenerator(CentralWidget *cw, QVector<Config *> configs)
{
    this->configs = configs;
    this->cw = cw;
    connect(this, SIGNAL(emitClearImage(int)), this->cw, SLOT(receiveClearImage(int)));
}

void ThreadGenerator::run()
{
    Session *session;
    Config *config;
    int expectedNbVertices;

    foreach (config, this->configs) {
        for (int i = 0; i < config->getNbRuns(); i++)
        {
            expectedNbVertices = std::min((int) config->getEndMethod()->getMaxNumber(), (int) config->getEndMethod()->getLimitTime() * 1000 / config->getSleepTime());
            emit emitClearImage(expectedNbVertices);
            connect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));
           // connect(config, SIGNAL(emitUpdateImage()), this->cw, SLOT(receiveUpdateImage()));
            session = new Session(config);
            config->getGenerator()->setSession(session);
            session->generate();
            disconnect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));
            //disconnect(config, SIGNAL(emitUpdateImage()), this->cw, SLOT(receiveUpdateImage()));
        }
    }
}