#include "session.h"
#include "generators/treegenerator.h"
#include "endmethods/endmethod.h"
#include "environment/environment.h"
#include "src/classes/metrics/metric.h"
#include "heightmap.h"
#include "src/classes/config.h"
#include <QDebug>

/**
 * @brief Constructor
 * @param delta_t Time (so distance, in our case) between 2 points in the tree
 * @param environment Environment where the tree will be created and stored
 * @param metric Metric to calculate distance between points
 * @param generator Generator of new vertices at every iteration
 * @param map Map of the space
 */
Session::Session(Config* config)
{
    // Initialization of attributes
    this->delta_t = config->getDelta_t();
    Vertex *startVertex = new Vertex(config->getCurrentMap()->getStart(), NULL);
    this->environment = new Environment(this, config->getCurrentMap()->getWidth(), config->getCurrentMap()->getHeight(), startVertex);
    this->metric = config->getMetric();
    this->generator = config->getGenerator();
    this->map = config->getCurrentMap();
    this->endMethod = config->getEndMethod();
    this->config = config;
    srand(time(NULL));

    //connect(this, SIGNAL(emitDrawElement(Vertex*)), config, SLOT(receiveDrawElement(Vertex*)));
    //connect(this, SIGNAL(emitUpdateImage()), config, SLOT(receiveUpdateImage()));
}

/**
 * @brief Returns the time (so distance, in our case) between 2 points in the tree
 * @return Movement distance
 */
double Session::getDeltaT()
{
    return this->delta_t;
}

/**
 * @brief Returns the map's width
 * @return Map's width
 */
int Session::getWidth()
{
    return this->map->getWidth();
}

/**
 * @brief Returns the map's height
 * @return Map's Height
 */
int Session::getHeight()
{
    return this->map->getHeight();
}

/**
 * @brief Returns the environment where the tree will be created and stored
 * @return Environment
 */
Environment* Session::getEnvironment()
{
    return this->environment;
}

/**
 * @brief Returns the metric used to calculate distance between points
 * @return Metric used
 */
Metric* Session::getMetric()
{
    return this->metric;
}

/**
 * @brief Returns the generator of new vertices at every iteration
 * @return Generator used
 */
TreeGenerator* Session::getGenerator()
{
    return this->generator;
}

/**
 * @brief Returns the map of the space
 * @return Map of the space
 */
HeightMap* Session::getMap()
{
    return this->map;
}

void Session::generate()
{

    while (!this->endMethod->isOver())
    {
        qDebug() << "Vertex to generate";
        Vertex* vertex = this->generator->generate();
        qDebug() << "Vertex generated";
        this->environment->addElement(vertex);
        qDebug() << "Vertex added";
        this->config->receiveDrawElement(vertex);
        qDebug() << "signal draw sent";
        this->config->receiveUpdateImage();
        qDebug() << "signal update sent";
        //emit emitDrawElement(vertex);
        //QThread::msleep(this->config->getSleepTime());
    }

    this->config->receiveUpdateImage();
    //emit emitUpdateImage();
}

/**
 * @brief Uses the heightmap to determine if a point is an obstacle
 * @param point Point to test
 *//*
bool Session::isObstacle(QPointF point)
{
    return this->map->isObstacle(point);
}*/

/**
 * @brief Uses the heightmap to determine if a path is free of obstacles
 * @param point1 Starting point of the path
 * @param point2 Arrival point of the path
 * @return true if the path is obstacle free, false otherwise
 */
bool Session::isPathFree(QPointF point1, QPointF point2)
{
    return this->map->isPathFree(point1, point2);
}

/**
 * @brief Returns a random vertex of the tree, using the environment
 * @return Random vertex
 */
Vertex* Session::getRandomVertex()
{
    return this->environment->getRandomVertex();
}

/**
 * @brief Returns the closest vertex of the tree from the given point
 * @param point Point of the environment
 * @return Closest vertex
 */
Vertex* Session::getClosestVertex(QPointF point)
{

    return this->environment->getClosestNaive(point);
}

/**
 * @brief Calculates the distance between 2 points according to the metric
 * @param from First point
 * @param to Second point
 * @return Distance between the first and second points
 */
double Session::distance(QPointF from, QPointF to)
{
    return this->metric->distance(from, to);
}
