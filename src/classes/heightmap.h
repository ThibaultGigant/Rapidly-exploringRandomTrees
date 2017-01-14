#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QString>
#include <QFile>
#include <iostream>
#include <QDebug>
#include <random>
#include <cmath>


using namespace std;

class HeightMap : public QObject
{
public:

    HeightMap(QString name, int width, int height, QPointF *start = new QPointF(0,0), QPointF *end = new QPointF(0,0));

    void clearObstacles();

    QString toFileString();
    void loadFromString(QString fileString);


    static HeightMap* hmFromFile(QString fileName);
    QVector<QVector<int> > getMap();
    void setMap(QVector<QVector<int> > map);

    int getHeight();
    int getWidth();

    QPointF* getStart();
    QPointF* getEnd();
    QString getName();

    QString setName(QString name);

    bool isObstacle(QPointF point);
    bool isPathFree(QPointF point1, QPointF point2);

    void setMapPixel(int x, int y, int val);

private:

    int width;
    int height;
    QString name;

    QVector<QVector<int> > map;

    QPointF *start;
    QPointF *end;

    void resizeMap(int width, int height);


public slots:

    void setPixel(int x,int y, int val);
    void clearMap();

};

#endif // HEIGHTMAP_H
