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
    int WIDTH = 600;
    int HEIGHT = 600;
    QString NAME = "name";
    QPointF START_POINT = QPointF (WIDTH / 2, HEIGHT / 2);
    QPointF END_POINT = QPointF (0, 0);



    Config();

    HeightMap *getCurrentMap();
    void setCurrentMap(HeightMap * map);
    Metric* getMetric();
    void setMetric(Metric *metric);
    TreeGenerator* getGenerator();
    void setGenerator(TreeGenerator *generator);

    EndMethod *getEndMethod();
    void setEndMethod(EndMethod *value);

public slots:
    void receiveDrawElement(Vertex *vertex);

    void startRun();
    void stopRun();

signals:
    void emitDrawElement(Vertex *vertex);


private :

    bool isRunning;

    HeightMap *currentMap;
    Metric *metric;
    TreeGenerator *generator;
    EndMethod *endMethod;




};

#endif // CONFIG_H
