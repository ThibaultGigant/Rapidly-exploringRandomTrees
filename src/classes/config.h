#ifndef CONFIG_H
#define CONFIG_H

#include "heightmap.h"


class Config
{
public:
    Config();

    HeightMap *getViewMap();
    void setViewMap(HeightMap * map);

private :

    HeightMap *viewMap;

};

#endif // CONFIG_H
