#include "config.h"

Config::Config()
{


}

HeightMap* Config::getViewMap(){
    return this->viewMap;
}

void Config::setViewMap(HeightMap * map){
    this->viewMap = map;
}
