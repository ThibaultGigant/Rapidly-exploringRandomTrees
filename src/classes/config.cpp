#include "config.h"


Config::Config()
{
    setCurrentMap(new HeightMap(NAME, WIDTH, HEIGHT, START_POINT, END_POINT));
}
/**
 * @brief Config::getCurrentMap
 * @return
 */
HeightMap* Config::getCurrentMap(){
    return this->currentMap;
}

/**
 * @brief Config::setCurrentMap
 * @param map
 */
void Config::setCurrentMap(HeightMap * map){
    this->currentMap = map;
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

EndMethod *Config::getEndMethod() const
{
    return endMethod;
}

void Config::setEndMethod(EndMethod *value)
{
    endMethod = value;
}
/**
 * @brief getHeightMapViewPanel
 * @return
 *//*
HeightMapViewPanel* Config::getHeightMapViewPanel(){
    return hmViemPanel;
}

void Config::setHeightMapViewPanel(HeightMapViewPanel* hmViewPanel){
    this->hmViemPanel = hmViewPanel;
}*/

void Config::receiveDrawElement(Vertex *vertex)
{
    emit emitDrawElement(vertex);
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
