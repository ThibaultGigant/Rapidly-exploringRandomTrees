#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H

#include <QString>

#include "metric.h"

class EuclidianDistance : public Metric
{
public:
    EuclidianDistance();
    ~EuclidianDistance();
    virtual double distance(QPointF point1, QPointF point2);
    virtual QString toString(void);
};

#endif // EUCLIDIANDISTANCE_H
