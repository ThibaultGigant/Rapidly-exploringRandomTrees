#include "randomtreegenerator.h"
#include "src/classes/session.h"

/**
 * @brief Constructor
 * @param session Session using this generator
 */
RandomTreeGenerator::RandomTreeGenerator(Session* session) : TreeGenerator(session)
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
    Vertex* vertex = this->session->getRandomVertex();
    double angle, newX, newY;
    QPointF point;

    do
    {
        angle = (rand() / (double) RAND_MAX) * (double) 2 * M_PI;
        newX = vertex->getPosition().x() + cos(angle);
        newY = vertex->getPosition().y() + sin(angle);
        point = QPointF(newX, newY);
    } while (this->session->isObstacle(point));
    return new Vertex(point, vertex);
}
