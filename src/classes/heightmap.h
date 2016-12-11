#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H


#include <QPointF>
#include <QVector>
#include <QString>

class HeightMap
{
public:

    HeightMap(QString name, int width, int height, QPointF start = QPointF(0,0), QPointF end = QPointF(0,0));

    void clearObstacles();
    QString toFileString();
    void loadFromString(QString fileString);

    QVector<QVector<int> > getMap();

    int getHeight();
    int getWidth();

    QPointF getStart();
    QPointF getEnd();
    QString getName();

    bool isObstacle(QPointF point);

private:

    int width;
    int height;
    QString name;

    QVector<QVector<int> > map;

    QPointF start;
    QPointF end;

    void resizeMap(int width, int height);

};

#endif // HEIGHTMAP_H
