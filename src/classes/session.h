#ifndef SESSION_H
#define SESSION_H

#include <QPointF>
#include <ctime>
#include <cstdlib>

class Environment;
class TreeGenerator;
class HeightMap;
class EndMethod;
class Metric;
class Vertex;
class Config;

class Session
{
public:
    Session(double delta_t, Metric* metric, TreeGenerator* generator, HeightMap* map, Config* config);
    ~Session();

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

private:
    // Attributes
    double delta_t;
    Metric* metric;
    Environment* environment;
    TreeGenerator* generator;
    HeightMap* map;
    EndMethod* endMethod;
    Config* config;

    bool isOver;

    // Methods
    void generate();
};

#endif // SESSION_H
