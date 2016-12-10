#ifndef SESSION_H
#define SESSION_H

#include "Metriques/metric.h"
#include "environment.h"

class Session
{
public:
    Session();
    ~Session();
    Metric metric;
    Environment environment;
};

#endif // SESSION_H
