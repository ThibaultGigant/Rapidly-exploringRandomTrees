#ifndef CONFIG_H
#define CONFIG_H

#include "heightmap.h"
#include "src/classes/environment/vertex.h"

class HeightMapViewPanel;
class Vertex;

class Config: public QObject
{
    Q_OBJECT
public:
    int WIDTH = 600;
    int HEIGHT = 400;
    QString NAME = "name";
    QPointF START_POINT = QPointF (0,0);
    QPointF END_POINT = QPointF (WIDTH / 2, HEIGHT / 2);



    Config();

    HeightMap *getCurrentMap();
    void setCurrentMap(HeightMap * map);

    HeightMapViewPanel* getHeightMapViewPanel();
    void setHeightMapViewPanel(HeightMapViewPanel* hmViewPanel);

public slots:
    void receiveDrawElement(Vertex *vertex);

    void startRun();
    void stopRun();

signals:
    void emitDrawElement(Vertex *vertex);


private :

    bool isRunning;

    HeightMap *currentMap;




};

#endif // CONFIG_H
