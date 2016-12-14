#include "heightmap.h"
#include <random>

/**
 * @brief HeightMap::HeightMap
 * @param name
 * @param width
 * @param height
 * @param start
 * @param end
 */
HeightMap::HeightMap(QString name, int width, int height, QPointF start, QPointF end){

    //qDebug() << "This is a test";
    this->name = name;
    this->width = width;
    this->height = height;
    this->start = start;
    this->end = end;
    this->map = QVector< QVector<int> >();

    for (int i = 0; i< width ; i ++){
        QVector<int> column;
        this->map.append(column);
        for(int j = 0;j < height ; j++){
            //this->map.last().append(rand()%256);
            this->map.last().append(0);
        }
    }
    for (int i = 50; i< width-50 ; i ++){
        this->map[i][this->getHeight() * 2/ 3] = 255;
    }
}


/**
 * @brief HeightMap::resizeMap
 * @param width
 * @param height
 */
void HeightMap::resizeMap(int width, int height){


    QVector<QVector<int> > temp = QVector<QVector<int> >(height);

    for (int i = 0; i< width ; i ++){
        temp[i] = QVector<int>(height);
        for(int j = 0;j < height ; j ++){
            if ( i < this->width && j < this->height){
                temp[i][j] = map[i][j];
            }else{
                temp[i][j] = 0;
            }
        }
    }

    this->width = width;
    this->height = height;

    this->map = temp;

}

/**
 * @brief HeightMap::clearObstacles
 */
void HeightMap::clearObstacles(){
    for (int i = 0; i< width ; i ++){
        for(int j = 0;j < height ; j ++){
            map[i][j] = 0;
        }
    }
}

/**
 * @brief HeightMap::getName
 * @return
 */
QString HeightMap::getName(){
    return name;
}

/**
 * @brief HeightMap::getHeight
 * @return
 */
int HeightMap::getHeight(){
    return height;
}

/**
 * @brief HeightMap::getWidth
 * @return
 */
int HeightMap::getWidth(){
    return width;
}

/**
 * @brief HeightMap::getStart
 * @return
 */
QPointF HeightMap::getStart(){
    return start;
}

/**
 * @brief HeightMap::getEnd
 * @return
 */
QPointF HeightMap::getEnd(){
    return end;
}

QVector<QVector<int> > HeightMap::getMap()
{
    return this->map;
}

/**
 * @brief Returns a string corresponding to the file format of the map
 * @return QString
 */
QString HeightMap::toFileString(){
    QString str = QString();
    str += name+"/n";
    str += QString::number(width) + " ";
    str += QString::number(height) + "/n";
    str += QString::number(start.x()) + " ";
    str += QString::number(start.y())  + "/n";
    str += QString::number(end.x()) + " ";
    str += QString::number(end.y())  + "/n";

    for (int i = 0; i< width ; i ++){
        for(int j = 0;j < height ; i ++){
            str+= QString::number(map[i][j]) + " ";
        }
        str+="/n";
    }
    return str;
}

/**
 * @brief Verifies if a point is in an obstacle
 * @param point Point to test
 * @return true if it's an obstacle, false otherwise
 */
bool HeightMap::isObstacle(QPointF point)
{
    int colonne = (int) (point.x() / width);
    int ligne = (int) (point.y() / height);
    return this->map[colonne][ligne] > 0;
}

/**
 * @brief Set the value of a pixel (x,y) to val
 * @param x
 * @param y
 * @param val
 */
void HeightMap::setPixel(int x, int y, int val){
    map[x][y] = val;
}


/**
 * @brief Clear the map : set all the pixels to 0
 */
void HeightMap::clearMap(){
    clearObstacles();
}











