#include "endmethod.h"

/**
 * @brief Constructor
 * @param maxNumber Maximum number of vertices to generate
 * @param duration Maximum duration of the simulation
 */
EndMethod::EndMethod(quint64 maxNumber, time_t duration)
{
    this->nbVertices = 0;
    this->maxNumber = maxNumber;
    this->duration = duration;
    this->startTime = 0;

    if (this->maxNumber == 0 && this->duration == 0)
        this->maxNumber = 1;
}

/**
 * @brief Destructor
 */
EndMethod::~EndMethod()
{}

/**
 * @brief Getter of the number of vertices to create
 * @return Number of vertices
 */
quint64 EndMethod::getMaxNumber() const
{
    return maxNumber;
}

/**
 * @brief Sets the number of vertices to create
 * @param value Number of vertices to create
 */
void EndMethod::setMaxNumber(const quint64 &value)
{
    maxNumber = value;
}

/**
 * @brief Sets the maximum duration of the simulation
 * @param value New value of the duration
 */
void EndMethod::setDuration(const time_t &value)
{
    duration = value;
}

/**
 * @brief Getter of the end time of the program
 * @return The end time
 */
time_t EndMethod::getLimitTime() const
{
    return duration;
}

/**
 * @brief Getter of the number of vertices currently in the tree
 * @return The number
 */
quint64 EndMethod::getNbVertices() const
{
    return nbVertices;
}


/**
 * @brief Verifies if the generation of vertices should stop
 * @return true if the generation should be over, false otherwise
 */
bool EndMethod::isOver()
{
    return isTimeOver() || isNbVerticesOver();
}


/**
 * @brief Verifies if the generation should be over due to time limitation
 * @return true if the generation should be over, false otherwise
 */
bool EndMethod::isTimeOver()
{
    // Initialization of the start time
    if (this->startTime == 0)
        this->startTime = time(0);

    if (this->duration > 0 && time(0) >= this->startTime + this->duration)
        return true;
    return false;
}

/**
 * @brief Verifies if the generation has reached the right number of vertices
 * @return true if the generation should be over, false otherwise
 */
bool EndMethod::isNbVerticesOver()
{
    this->nbVertices += 1;
    if (this->maxNumber > 0 && this->nbVertices >= this->maxNumber)
        return true;
    return false;
}

/**
 * @brief Resets the endmethod to it's original value
 */
void EndMethod::reset()
{
    this->nbVertices = 0;
    this->startTime = 0;
}

QString EndMethod::toString()
{
    return "";
}
