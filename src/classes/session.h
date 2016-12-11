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

class Session
{
public:
    Session(double delta_t, Environment* environment, Metric* metric, TreeGenerator* generator, HeightMap* map);
    ~Session();
    double getDeltaT();
    Environment* getEnvironment();
    Metric* getMetric();
    TreeGenerator* getGenerator();
    HeightMap* getMap();
    bool isObstacle(QPointF point);
    Vertex* getRandomVertex();

private:
    // Attributes
    double delta_t;
    Metric* metric;
    Environment* environment;
    TreeGenerator* generator;
    HeightMap* map;
    EndMethod* endMethod;
    bool isOver;

    // Methods
    void generate();
};

#endif // SESSION_H
