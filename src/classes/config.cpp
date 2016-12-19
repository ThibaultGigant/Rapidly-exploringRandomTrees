#include "config.h"
#include "endmethods/endmethod.h"

Config::Config()
{
}

/**
 * @brief Returns the map used in this configuration
 * @return Map used
 */
HeightMap* Config::getCurrentMap(){
    return this->currentMap;
}

/**
 * @brief Sets the map to use in this configuration
 * @param map Map to use
 */
void Config::setCurrentMap(HeightMap * map){
    this->currentMap = map;
}

/**
 * @brief Resets everything so a new run can be performed
 */
void Config::reset()
{
    this->endMethod->reset();
}

/**
 * @brief Config::startRun
 */
void Config::startRun(){
    this->isRunning = true;
}

/**
 * @brief Config::stopRun
 */
void Config::stopRun(){
    this->isRunning = false;
}

EndMethod *Config::getEndMethod()
{
    return endMethod;
}

void Config::setEndMethod(EndMethod *value)
{
    endMethod = value;
}

void Config::receiveDrawElement(Vertex *vertex)
{
    emit emitDrawElement(vertex);
}

void Config::receiveUpdateImage(){
    emit emitUpdateImage();
}

double Config::getDelta_t() const
{
    return delta_t;
}

void Config::setDelta_t(double value)
{
    delta_t = value;
}

int Config::getNbRuns() const
{
    return nbRuns;
}

void Config::setNbRuns(int value)
{
    nbRuns = value;
}

int Config::getSleepTime() const
{
    return sleepTime;
}

void Config::setSleepTime(int value)
{
    sleepTime = value;
}

Metric* Config::getMetric()
{
    return this->metric;
}

void Config::setMetric(Metric *metric)
{
    this->metric = metric;
}

TreeGenerator* Config::getGenerator()
{
    return this->generator;
}

void Config::setGenerator(TreeGenerator *generator)
{
    this->generator = generator;
}
