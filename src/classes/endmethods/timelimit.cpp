#include "timelimit.h"

/**
 * @brief Constructor
 * @param duration Duration in seconds of the simulation. After this time, no more vertices will be generated.
 */
TimeLimit::TimeLimit(quint64 duration)
{
    this->limitTime = time(0) + duration;
}

/**
 * @brief Destructor
 */
TimeLimit::~TimeLimit()
{}

/**
 * @brief Verifies if the generation should be over due to time limitation
 * @return true if the generation should be over, false otherwise
 */
bool TimeLimit::isOver()
{
    if (time(0) >= this->limitTime)
        return true;
    return false;
}
