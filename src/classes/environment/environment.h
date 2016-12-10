#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QVector>
#include <QPointF>
#include <cmath>
#include "vertex.h"
#include "quadrant.h"
#include "src/classes/session.h"

class Environment
{
public:
    Environment(Session* session, int width, int height,Vertex* vertex);
    ~Environment();
    void addElement(Vertex *vertex);
    Vertex* getClosest(QPointF point);

private:
    int width;
    int height;
    int nbLines;
    int nbColumns;
    Session* session;
    Vertex* startVertex;
    QVector<QVector<Quadrant> > quadrants;
};

#endif // ENVIRONMENT_H
