#ifndef METRIC_H
#define METRIC_H

#include <QPointF>
#include <cmath>
#include <QString>

class Metric
{
public:
    Metric();
    ~Metric();
    virtual double distance(QPointF point1, QPointF point2);
    virtual QString toString(void);
};

#endif // METRIC_H
