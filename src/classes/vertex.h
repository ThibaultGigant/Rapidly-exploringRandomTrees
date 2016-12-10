#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <QPointF>

class Vertex
{

public:
    Vertex(QPointF position, Vertex* parent);
    ~Vertex();
    QPointF getPosition();
    Vertex* getParent();

private:
    QPointF position;
    Vertex* parent;

};

#endif // VERTEX_H
