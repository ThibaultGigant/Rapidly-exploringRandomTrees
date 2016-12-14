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
    qDebug() << "Generation RRT";
    // Initializing variables
    Vertex* vertex;
    double angle, newX, newY;
    QPointF point;

    do
    {
        qDebug() << "Avant random";
        // Determining a random point
        newX = (rand() / (double) RAND_MAX) * this->session->getWidth();
        newY = (rand() / (double) RAND_MAX) * this->session->getHeight();
        point = QPointF(newX, newY);

        qDebug() << "Avant getclosest";
        vertex = this->session->getClosestVertex(point);

        qDebug() << "Avant distance";
        if (this->session->distance(point, vertex->getPosition()))
            return new Vertex(point, vertex);

        newX -= vertex->getPosition().x();
        newY -= vertex->getPosition().y();
        angle = atan2(newY, newX);
        newX = vertex->getPosition().x() + cos(angle);
        newY = vertex->getPosition().y() + sin(angle);
        point = QPointF(newX, newY);
    } while (this->session->isObstacle(point));
    return new Vertex(point, vertex);
}

