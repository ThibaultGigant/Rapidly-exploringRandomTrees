#ifndef CONFIG_H
#define CONFIG_H

#include "heightmap.h"
#include "src/classes/environment/vertex.h"

class HeightMapViewPanel;
class Vertex;
class Metric;
class TreeGenerator;
class EndMethod;

class Config: public QObject
{
    Q_OBJECT
public:
    Config();

    // Getters and setters
    HeightMap *getCurrentMap();
    void setCurrentMap(HeightMap * map);
    Metric* getMetric();
    void setMetric(Metric *metric);
    TreeGenerator* getGenerator();
    void setGenerator(TreeGenerator *generator);
    EndMethod *getEndMethod();
    void setEndMethod(EndMethod *value);
    int getNbRuns() const;
    void setNbRuns(int value);
    int getSleepTime() const;
    void setSleepTime(int value);
    double getDelta_t() const;
    void setDelta_t(double value);

    // Other methods
    void receiveDrawElement(Vertex *vertex);
    void receiveUpdateImage();


private :

    bool isRunning;

    HeightMap *currentMap;
    Metric *metric;
    TreeGenerator *generator;
    EndMethod *endMethod;

    int nbRuns;
    int sleepTime;
    double delta_t;

public slots:
    void startRun();
    void stopRun();

signals:
    void emitDrawElement(Vertex *vertex);
    void emitUpdateImage();

};

#endif // CONFIG_H
