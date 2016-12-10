#ifndef QUADRANT_H
#define QUADRANT_H

#include <QVector>
#include "vertex.h"

class Quadrant
{
public:
    Quadrant();
    ~Quadrant();
    void addVertex(Vertex* vertex);
    QVector<Vertex*> getVertices();

private:
    QVector<Vertex*> vertices;
};

#endif // QUADRANT_H
