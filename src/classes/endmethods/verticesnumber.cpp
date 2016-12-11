#include "verticesnumber.h"

/**
 * @brief Constructor
 * @param maxNumber Maximum number of vertices in the tree. Interrupts the generation of new vertices if there are more vertices in the tree than this number.
 */
VerticesNumber::VerticesNumber(quint64 maxNumber)
{
    this->nbVertices = 0;
    this->maxNumber = maxNumber;
}

/**
 * @brief Destructor
 */
VerticesNumber::~VerticesNumber()
{}

/**
 * @brief Verifies if the generation has reached the right number of vertices
 * @return true if the generation should be over, false otherwise
 */
bool VerticesNumber::isOver()
{
    this->nbVertices += 1;
    if (this->nbVertices >= this->maxNumber)
        return true;
    return false;
}
