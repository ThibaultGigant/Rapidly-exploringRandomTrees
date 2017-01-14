#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QVector>
#include <QPointF>
#include <cmath>
#include <cstdlib>
#include "vertex.h"
#include "quadrant.h"
#include "src/classes/session.h"

class Environment
{
public:
    Environment(Session* session, int width, int height,Vertex* vertex);
    ~Environment();
    void addElement(Vertex *vertex);
    Vertex* getClosestAround(QPointF point, int radius = 1);
    Vertex* getClosest(QPointF point);
    Vertex* getClosestAlmostNaive(QPointF point);
    Vertex* getClosestNaive(QPointF point);
    Vertex* getRandomVertex();
    QVector<Vertex *> getVertices() const;
    void setVertices(const QVector<Vertex *> &value);

private:
    int width;
    int height;
    int nbLines;
    int nbColumns;
    Session* session;
    Vertex* startVertex;
    QVector<Vertex *> vertices;
    QVector<QVector<Quadrant> > quadrants;
};

#endif // ENVIRONMENT_H
