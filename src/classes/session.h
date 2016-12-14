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
    Session(double delta_t, Config* config);
    //~Session();

    double getDeltaT();
    Environment* getEnvironment();
    Metric* getMetric();
    TreeGenerator* getGenerator();
    HeightMap* getMap();

    bool isObstacle(QPointF point);
    Vertex* getRandomVertex();
    Vertex* getClosestVertex(QPointF point);
    int getWidth();
    int getHeight();
    double distance(QPointF from, QPointF to);
    void generate();

private:
    // Attributes
    double delta_t;
    Metric* metric;
    Environment* environment;
    TreeGenerator* generator;
    HeightMap* map;
    EndMethod* endMethod;
    Config* config;

    // Methods

signals:
    void emitDrawElement(Vertex *vertex);

};

#endif // SESSION_H
