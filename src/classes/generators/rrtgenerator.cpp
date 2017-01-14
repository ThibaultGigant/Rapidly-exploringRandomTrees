#include "rrtgenerator.h"
#include "src/classes/session.h"
#include <QDebug>

/**
 * @brief Constructor
 * @param session Session using this generator
 */
RRTGenerator::RRTGenerator() : TreeGenerator()
{
}

/**
 * @brief Destructor
 */
RRTGenerator::~RRTGenerator()
{}

/**
 * @brief Generates a new vertex according to the RRT algorithm
 * @return New Vertex generated, to be added
 */
Vertex* RRTGenerator::generate()
{

    // Initializing variables
    Vertex* vertex;
    double angle, newX, newY;
    QPointF point;

    do
    {

        // Determining a random point
        newX = (rand() / (double) RAND_MAX) * this->session->getWidth();
        newY = (rand() / (double) RAND_MAX) * this->session->getHeight();
        point = QPointF(newX, newY);

        vertex = this->session->getClosestVertex(point);

        if (this->session->distance(point, vertex->getPosition()) < this->session->getDeltaT() &&
                this->session->isPathFree(vertex->getPosition(), point))
            return new Vertex(point, vertex);

        newX -= vertex->getPosition().x();
        newY -= vertex->getPosition().y();
        angle = atan2(newY, newX);
        newX = vertex->getPosition().x() + cos(angle) * this->getSession()->getDeltaT();
        newY = vertex->getPosition().y() + sin(angle) * this->getSession()->getDeltaT();
        point = QPointF(newX, newY);
    } while (!(this->session->isPathFree(vertex->getPosition(), point)));
    return new Vertex(point, vertex);
}

/**
 * @brief Displays the type of algorithm used for the generation of the tree
 * @return String of the generation algorithm
 */
QString RRTGenerator::toString()
{
    return "RRT Algorithm";
}
