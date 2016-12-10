#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H

#include "metric.h"

class EuclidianDistance : public Metric
{
public:
    EuclidianDistance();
    ~EuclidianDistance();
    virtual double distance(QPointF point1, QPointF point2);
};

#endif // EUCLIDIANDISTANCE_H
