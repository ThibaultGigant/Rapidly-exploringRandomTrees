#include "threadgenerator.h"
#include <algorithm>

ThreadGenerator::ThreadGenerator(CentralWidget *cw, QVector<Config *> configs)
{
    this->configs = configs;
    this->cw = cw;
    connect(this, SIGNAL(emitClearImage(int)), this->cw, SLOT(receiveClearImage(int)));
    connect(this, SIGNAL(emitDone()), this->cw, SLOT(done()));
}

void ThreadGenerator::run()
{
    Session *session;
    Config *config;
    int expectedNbVertices;

    foreach (config, this->configs) {
        for (int i = 0; i < config->getNbRuns(); i++)
        {
            config->reset();
            this->cw->setCurrentMap(config->getCurrentMap());
            if (config->getEndMethod()->getMaxNumber() > 0 && config->getEndMethod()->getLimitTime() > 0)
                expectedNbVertices = std::min((int) config->getEndMethod()->getMaxNumber(), (int) config->getEndMethod()->getLimitTime() * 1000 / config->getSleepTime());
            else if (config->getEndMethod()->getMaxNumber() > 0)
                expectedNbVertices = config->getEndMethod()->getMaxNumber();
            else
                expectedNbVertices = config->getEndMethod()->getLimitTime() * 1000 / config->getSleepTime();

            emit emitClearImage(expectedNbVertices);

            connect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));
           // connect(config, SIGNAL(emitUpdateImage()), this->cw, SLOT(receiveUpdateImage()));
            session = new Session(config);
            config->getGenerator()->setSession(session);
            session->generate();
            disconnect(config, SIGNAL(emitDrawElement(Vertex*)), this->cw, SLOT(receiveDrawElement(Vertex*)));
            //disconnect(config, SIGNAL(emitUpdateImage()), this->cw, SLOT(receiveUpdateImage()));
            delete session;
        }
    }
    emit emitDone();
}
