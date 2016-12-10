#include "quadrant.h"

/**
 * @brief Constructor
 */
Quadrant::Quadrant()
{

    this->vertices = QVector<Vertex *>();
}

/**
 * @brief Destructor
 */
Quadrant::~Quadrant()
{


    for (int i = 0; i < this->vertices.size(); i++)
        delete(this->vertices[i]);
    this->vertices.clear();
}

/**
 * @brief Adds a vertex to the quadrant
 * @param vertex Vertex to add
 */
void Quadrant::addVertex(Vertex* vertex)
{
    this->vertices.append(vertex);
}

/**
 * @brief Returns all vertices inside the quadrant
 * @return QVector of those vertices pointers
 */
QVector<Vertex*> Quadrant::getVertices()
{
    return this->vertices;
}
