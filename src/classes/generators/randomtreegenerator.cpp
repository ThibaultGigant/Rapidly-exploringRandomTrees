#include "randomtreegenerator.h"
#include "src/classes/session.h"
#include <QDebug>

/**
 * @brief Constructor
 * @param session Session using this generator
 */
RandomTreeGenerator::RandomTreeGenerator() : TreeGenerator()
{
}

/**
 * @brief Destructor
 */
RandomTreeGenerator::~RandomTreeGenerator()
{}

/**
 * @brief Generates a new vertex connected to a random vertex of the tree
 * @return New Vertex generated, to be added
 */
Vertex* RandomTreeGenerator::generate()
{
    Vertex* vertex;
    double angle, newX, newY;
    QPointF point;

    do
    {
        vertex = this->session->getRandomVertex();
        angle = (rand() / (double) RAND_MAX) * (double) 2 * M_PI;
        newX = vertex->getPosition().x() + cos(angle) * this->getSession()->getDeltaT();
        newY = vertex->getPosition().y() + sin(angle) * this->getSession()->getDeltaT();
        point = QPointF(newX, newY);
    } while (!(this->session->isPathFree(vertex->getPosition(), point)));
    return new Vertex(point, vertex);
}
