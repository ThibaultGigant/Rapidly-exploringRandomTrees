#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "metric.h"

class ManhattanDistance : public Metric
{
public:
    ManhattanDistance();
    ~ManhattanDistance();
    virtual double distance(QPointF point1, QPointF point2);
};

#endif // MANHATTANDISTANCE_H
