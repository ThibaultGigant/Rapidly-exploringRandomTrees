#ifndef CONFIG_H
#define CONFIG_H

#include "heightmap.h"

class HeightMapViewPanel;


class Config
{
public:
    Config();

    HeightMap *getCurrentMap();
    void setCurrentMap(HeightMap * map);

    HeightMapViewPanel* getHeightMapViewPanel();
    void setHeightMapViewPanel(HeightMapViewPanel* hmViewPanel);

public slots:

    void startRun();
    void stopRun();


private :

    bool isRunning;

    HeightMap *currentMap;
    HeightMapViewPanel* hmViemPanel;



};

#endif // CONFIG_H
