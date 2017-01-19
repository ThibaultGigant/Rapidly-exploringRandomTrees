#include "manhattandistance.h"

/**
 * @brief Constructor
 */
ManhattanDistance::ManhattanDistance()
{}

/**
 * @brief Destructor
 */
ManhattanDistance::~ManhattanDistance()
{}

/**
 * @brief Calculates the Manhattan distance betwen 2 points
 * @param point1 First point
 * @param point2 Second point
 * @return Distance between point1 and point2
 */
double ManhattanDistance::distance(QPointF point1, QPointF point2)
{
    QPointF temp = point2-point1;
    return temp.manhattanLength();
}

QString ManhattanDistance::toString(){
    return "Manhattan Distance";
}
