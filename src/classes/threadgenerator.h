#ifndef THREADGENERATOR_H
#define THREADGENERATOR_H

#include <QThread>
#include <QDir>
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
    Vertex *lastVertexDrawn;
    bool stopSimulations;
    Session *session;
    QString dirPath;
    QVector<HeightMap*> savedMaps;

    bool save;

    int configCount = 0;
    int runCount = 0;

    bool saveConfig();
    bool saveRunFile(Session *);
    bool ThreadGenerator::saveHeightMap(HeightMap *map);


protected:
    void run();

signals:
    void emitClearImage(int);
    void emitDone();
    void emitStop();

public slots:
    void getVertexDrawn(Vertex* v);
    void skipToNext();
    void stop();
};

#endif // THREADGENERATOR_H
