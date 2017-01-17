#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include <QDebug>

class HeightMapViewPanel;
class HeightMap;
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
    int getMetricID() const;
    void setMetricID(int value);
    int getGeneratorID() const;
    void setGeneratorID(int value);
    int getKForPRM() const;
    void setKForPRM(int value);
    qint64 getNbVerticesLimit() const;
    void setNbVerticesLimit(const qint64 &value);
    time_t getTimeDuration() const;
    void setTimeDuration(const time_t &value);


    // Other methods
    void receiveDrawElement(Vertex *vertex);
    void receiveUpdateImage();
    void reset();
    QString toString();


private :

    bool isRunning;

    HeightMap *currentMap;
    Metric *metric;
    TreeGenerator *generator;
    EndMethod *endMethod;

    int metricID;
    int generatorID;
    int kForPRM;
    qint64 nbVerticesLimit;
    time_t timeDuration;

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
