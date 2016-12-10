#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QVector>
#include <QPointF>
#include "vertex.h"
#include "quadrant.h"

class Environment
{
public:
    Environment(int width, int height,Vertex* vertex);
    ~Environment();
    void addElement(Vertex *vertex);
    Vertex* getClosest(QPointF point);

private:
    int width;
    int height;
    Vertex* startVertex;
    QVector<QVector<Quadrant> > quadrants;
};

#endif // ENVIRONMENT_H
