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
    this->children = QVector<Vertex*>();

    if (parent)
        parent->addChild(this);
}

/**
 * @brief Vertex::~Vertex Destructor
 */
Vertex::~Vertex()
{
    this->children.clear();
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

/**
 * @brief Adds a child to the vertex
 * @param child Child vertex to add
 */
void Vertex::addChild(Vertex *child)
{
    this->children.append(child);
}

/**
 * @brief Returns the list of children of the vertex
 * @return List of children
 */
QVector<Vertex *> Vertex::getChildren() const
{
    return children;
}
