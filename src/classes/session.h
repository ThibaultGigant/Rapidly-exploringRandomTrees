#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QPointF>
#include <ctime>
#include <cstdlib>
#include <QThread>

class Environment;
class TreeGenerator;
class HeightMap;
class EndMethod;
class Metric;
class Vertex;
class Config;

class Session: public QObject
{
    Q_OBJECT
public:
    Session(Config* config);
    ~Session();

    double getDeltaT();
    Environment* getEnvironment();
    Metric* getMetric();
    TreeGenerator* getGenerator();
    HeightMap* getMap();

    //bool isObstacle(QPointF point);
    bool isPathFree(QPointF point1, QPointF point2);
    Vertex* getRandomVertex();
    Vertex* getClosestVertex(QPointF point);
    int getWidth();
    int getHeight();
    double distance(QPointF from, QPointF to);
    Vertex* generate();

private:
    // Attributes
    double delta_t;
    Metric* metric;
    Environment* environment;
    TreeGenerator* generator;
    HeightMap* map;
    EndMethod* endMethod;
    Config* config;
    bool next;

    // Methods

signals:

public slots:
    void stop();
};

#endif // SESSION_H
