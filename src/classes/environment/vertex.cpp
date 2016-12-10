#include "vertex.h"

/**
 * @brief Constructor
 * @param position Vertex's Position in the environment
 * @param parent Vertex's parent in the tree
 */
Vertex::Vertex(QPointF position, Vertex* parent)
{
    this->parent = parent;
    this->position = position;
}

/**
 * @brief Vertex::~Vertex Destructor
 */
Vertex::~Vertex()
{
}

/**
 * @brief Getter of the position
 * @return Vertex's position
 */
QPointF Vertex::getPosition()
{
    return this->position;
}

/**
 * @brief Getter of the parent
 * @return Parent du sommet dans l'arbre
 */
Vertex* Vertex::getParent()
{
    return this->parent;
}
