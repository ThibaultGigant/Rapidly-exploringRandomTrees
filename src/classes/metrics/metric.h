#ifndef METRIC_H
#define METRIC_H

#include <QPointF>
#include <cmath>

class Metric
{
public:
    Metric();
    ~Metric();
    virtual double distance(QPointF point1, QPointF point2);
};

#endif // METRIC_H
