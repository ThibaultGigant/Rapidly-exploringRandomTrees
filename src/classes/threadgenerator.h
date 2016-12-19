#ifndef THREADGENERATOR_H
#define THREADGENERATOR_H

#include <QThread>
#include "config.h"
#include "session.h"
#include "generators/treegenerator.h"
#include "src/app/centralwidget.h"

class ThreadGenerator : public QThread
{
    Q_OBJECT
public:
    ThreadGenerator(CentralWidget *cw, QVector<Config *> configs);

private:
    QVector<Config *> configs;
    CentralWidget *cw;

protected:
    void run();

signals:
    void emitClearImage(int);
};

#endif // THREADGENERATOR_H