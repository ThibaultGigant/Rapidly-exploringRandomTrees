#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "metric.h"

#include <QString>

class ManhattanDistance : public Metric
{
public:
    ManhattanDistance();
    ~ManhattanDistance();
    virtual double distance(QPointF point1, QPointF point2);
    virtual QString toString(void);
};

#endif // MANHATTANDISTANCE_H
