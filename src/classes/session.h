#ifndef SESSION_H
#define SESSION_H

#include "src/classes/metrics/metric.h"

class Environment;
class TreeGenerator;
class HeightMap;

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

private:
    double delta_t;
    Metric* metric;
    Environment* environment;
    TreeGenerator* generator;
    HeightMap* map;
};

#endif // SESSION_H
