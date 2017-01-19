#include "config.h"
#include "endmethods/endmethod.h"
#include "src/classes/generators/treegenerator.h"
#include "heightmap.h"
#include "src/classes/environment/vertex.h"
#include "src/classes/metrics/euclidiandistance.h"
#include "src/classes/metrics/manhattandistance.h"
#include "src/classes/generators/prmgenerator.h"
#include "src/classes/generators/randomtreegenerator.h"
#include "src/classes/generators/rrtgenerator.h"

Config::Config()
{
    this->kForPRM = 10;
    this->nbVerticesLimit = 100;
    this->timeDuration = 10;
}

/**
 * @brief Displays the Config information
 * @return String describing the config
 */
QString Config::toString(){

    QString res = "";

    res+=currentMap->getName()+"\n";
    res+=endMethod->toString()+"\n";
    res+=generator->toString()+"\n";
    res+=metric->toString()+"\n";
    res+=QString::number(delta_t)+"\n";

    return res;
}

/**
 * @brief Getter of the metric ID
 * @return Metric ID
 */
int Config::getMetricID() const
{
    return metricID;
}

/**
 * @brief Setter of the metric ID, but also sets the metric to the corresponding one
 * @param value New value of the metric ID
 */
void Config::setMetricID(int value)
{
    metricID = value;

    // Creation of the new metric
    if (value == 0)
        this->metric = new EuclidianDistance();
    else if (value == 1)
        this->metric = new ManhattanDistance();
    else
    {
        qDebug() << "Config : Wrong value for setMetricID. Got " << value << " but only 0 or 1 are allowed\nDefault set to Euclidian Distance";
        this->metric = new EuclidianDistance();
    }
}

/**
 * @brief Getter of the generator ID
 * @return Generator ID
 */
int Config::getGeneratorID() const
{
    return generatorID;
}

/**
 * @brief Sets the generator ID, and also changes the object stored in the generator attribute
 * @param value New value for the generator
 */
void Config::setGeneratorID(int value)
{
    generatorID = value;

    // Creation of the new generator
    if (value == 0)
        this->generator = new RandomTreeGenerator();
    else if (value == 1)
        this->generator = new RRTGenerator();
    else if (value == 2)
        this->generator = new PRMGenerator(this->getKForPRM());
    else
    {
        qDebug() << "Config : Wrong value for setGeneratorID. Got " << value << " but only 0, 1 or 2 are allowed\nDefault set to RRTGenerator";
        this->generator = new RRTGenerator();
    }
}

/**
 * @brief Getter for the number of vertices to check when using the PRM algorithm
 * @return This number of vertices to check during PRM
 */
int Config::getKForPRM() const
{
    return kForPRM;
}

/**
 * @brief Sets the new number of PRM
 * @param value
 */
void Config::setKForPRM(int value)
{
    kForPRM = value;
    try
    {
        PRMGenerator *gene = (PRMGenerator *) this->generator;
        gene->setNbToExamine(value);
    }
    catch (std::exception& bc)
    {
        qDebug() << "Config : Error casting, generator isn't a PRM Generator";
    }
}

/**
 * @brief Getter of the maximum number of vertices to generate
 * @return This number
 */
qint64 Config::getNbVerticesLimit() const
{
    return nbVerticesLimit;
}

/**
 * @brief Setter of the maximum number of vertices to generate, but also modifies the end method if it exists. If it doesn't, creates a new one
 * @param value New value of the maximum number of vertices to generate
 */
void Config::setNbVerticesLimit(const qint64 &value)
{
    nbVerticesLimit = value;
    if (this->endMethod)
        this->endMethod->setMaxNumber(value);
    else
        this->endMethod = new EndMethod(value);
}

/**
 * @brief Getter of the maximum duration of the generation
 * @return This duration
 */
time_t Config::getTimeDuration() const
{
    return timeDuration;
}

/**
 * @brief Setter of the maximum duration of the generation
 * If the end method already exists, changes its value, otherwise creates a new end method
 * @param value
 */
void Config::setTimeDuration(const time_t &value)
{
    timeDuration = value;
    if (this->endMethod)
        this->endMethod->setDuration(value);
    else
        this->endMethod = new EndMethod(0, value);
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

/**
 * @brief Returns the end method
 * @return End methos
 */
EndMethod *Config::getEndMethod()
{
    return endMethod;
}

/**
 * @brief Sets the end method to the new value
 * Also sets the attibutes timeDuration and nbVerticesLimit
 * @param value New end method to set
 */
void Config::setEndMethod(EndMethod *value)
{
    endMethod = value;

    this->timeDuration = value->getLimitTime();
    this->nbVerticesLimit = value->getMaxNumber();
}

/**
 * @brief Receive a vertex to draw, and informs the central widget of this vertex
 * @param vertex Vertex to draw
 */
void Config::receiveDrawElement(Vertex *vertex)
{
    emit emitDrawElement(vertex);
}

/**
 * @brief Receives a signal asking to clear the height map, and informs the central widget of this request
 */
void Config::receiveUpdateImage(){
    emit emitUpdateImage();
}

/**
 * @brief Returns the delta_t
 * @return delta_t attribute
 */
double Config::getDelta_t() const
{
    return delta_t;
}

/**
 * @brief Sets the delta_t to use
 * @param value New value of delta_t
 */
void Config::setDelta_t(double value)
{
    delta_t = value;
}

/**
 * @brief Returns the number of runs for this configuration
 * @return Number of runs
 */
int Config::getNbRuns() const
{
    return nbRuns;
}

/**
 * @brief Sets the number of runs for this configuration
 * @param value New value for this number
 */
void Config::setNbRuns(int value)
{
    nbRuns = value;
}

/**
 * @brief Returns the sleep time between the generation of 2 vertices
 * @return Sleep time
 */
int Config::getSleepTime() const
{
    return sleepTime;
}

/**
 * @brief Sets the sleep time between the generation of 2 vertices
 * @param value New value of this sleep time
 */
void Config::setSleepTime(int value)
{
    sleepTime = value;
}

/**
 * @brief Returns the metric used to calculate distances
 * @return The metric
 */
Metric* Config::getMetric()
{
    return this->metric;
}

/**
 * @brief Sets the metric to the new metric
 * @param metric New metric to use
 */
void Config::setMetric(Metric *metric)
{
    this->metric = metric;
}

/**
 * @brief Returns the generator for the tree
 * @return Genrator to use
 */
TreeGenerator* Config::getGenerator()
{
    return this->generator;
}

/**
 * @brief Sets the generator to use
 * @param generator New object to use as generator
 */
void Config::setGenerator(TreeGenerator *generator)
{
    this->generator = generator;
}

