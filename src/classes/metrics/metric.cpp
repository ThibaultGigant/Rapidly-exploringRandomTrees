#include "metric.h"

/**
 * @brief Constructor
 */
Metric::Metric()
{}

/**
 * @brief Destructor
 */
Metric::~Metric()
{}

/**
 * @brief Calculates the euclidian distance betwen 2 points
 * @param point1 First point
 * @param point2 Second point
 * @return Distance between point1 and point2
 */
double Metric::distance(QPointF point1, QPointF point2)
{
    QPointF temp = point2-point1;
    return sqrt(pow(temp.x(), 2) + pow(temp.y(), 2));
}

QString Metric::toString(){
    return "DEFAULT";
}
