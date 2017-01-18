#ifndef THREADGENERATOR_H
#define THREADGENERATOR_H

#include <QThread>
#include <QDir>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPair>
#include <QPainterPath>
#include "config.h"
#include "session.h"
#include "generators/treegenerator.h"
#include "src/app/centralwidget.h"

class ThreadGenerator : public QThread
{
    Q_OBJECT
public:
    ThreadGenerator(CentralWidget *cw, QVector<Config *> configs, QString dirPath = NULL);

    QString toString();

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

    float surfaceRatio;
    float surfaceRatioConnected;

    bool saveConfig(Config *conf);
    bool saveRunFile(Session *session);
    bool saveHeightMap(HeightMap *map);
    void drawHeightMap(HeightMap *map, unsigned char *data);
    bool generateAndSaveResultImage(QVector<Vertex*> vertices, float influence, HeightMap *map, QString path);

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
