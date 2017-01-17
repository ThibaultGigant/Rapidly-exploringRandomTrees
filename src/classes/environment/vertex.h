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
    int getId();
    void addChild(Vertex *child);
    QVector<Vertex *> getChildren() const;
    void setConnectedComponentPointer(Vertex *vertex);
    Vertex *getConnectedComponentPointer() const;

    QString toString();

    static int idCount;

    static int getUniqueId();
    static void resetVertexId();

private:
    QPointF position;
    Vertex* parent;
    QVector<Vertex *> children;
    Vertex* connectedComponentPointer;

    int id;

};

#endif // VERTEX_H
