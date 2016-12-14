#include "session.h"
#include "generators/treegenerator.h"
#include "endmethods/endmethod.h"
#include "environment/environment.h"
#include "src/classes/metrics/metric.h"
#include "heightmap.h"

/**
 * @brief Constructor
 * @param delta_t Time (so distance, in our case) between 2 points in the tree
 * @param environment Environment where the tree will be created and stored
 * @param metric Metric to calculate distance between points
 * @param generator Generator of new vertices at every iteration
 * @param map Map of the space
 */
Session::Session(double delta_t, Metric* metric, TreeGenerator* generator, HeightMap* map, Config* config)
{
    // Initialization of attributes
    this->delta_t = delta_t;
    Vertex *startVertex = new Vertex(map->getStart(), NULL);
    this->environment = new Environment(this, map->getWidth(), map->getHeight(), startVertex);
    this->metric = metric;
    this->generator = generator;
    this->map = map;
    this->config = config;
    srand(time(NULL));
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
    while (!this->isOver)
    {
        Vertex* vertex = this->generator->generate();
        this->environment->addElement(vertex);



        this->isOver = this->endMethod->isOver();
    }
}

/**
 * @brief Uses the heightmap to determine if a point is an obstacle
 * @param point Point to test
 */
bool Session::isObstacle(QPointF point)
{
    return this->map->isObstacle(point);
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
    return this->environment->getClosest(point);
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
