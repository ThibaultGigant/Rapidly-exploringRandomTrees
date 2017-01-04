#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <QPointF>
#include <QVector>

class Vertex
{

public:
    Vertex(QPointF position, Vertex* parent);
    ~Vertex();
    QPointF getPosition();
    Vertex* getParent();
    void addChild(Vertex *child);
    QVector<Vertex *> getChildren() const;

private:
    QPointF position;
    Vertex* parent;
    QVector<Vertex *> children;

};

#endif // VERTEX_H
