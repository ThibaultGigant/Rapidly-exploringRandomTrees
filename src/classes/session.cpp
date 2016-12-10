#include "session.h"

/**
 * @brief Constructor
 * @param delta_t Time (so distance, in our case) between 2 points in the tree
 * @param environment Environment where the tree will be created and stored
 * @param metric Metric to calculate distance between points
 * @param generator Generator of new vertices at every iteration
 * @param map Map of the space
 */
Session::Session(double delta_t, Environment* environment, Metric* metric, TreeGenerator* generator, HeightMap* map)
{
    // Initialization of attributes
    this->delta_t = delta_t;
    this->environment = environment;
    this->metric = metric;
    this->generator = generator;
    this->map = map;

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
