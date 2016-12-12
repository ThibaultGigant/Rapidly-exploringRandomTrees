#ifndef TREEGENERATOR_H
#define TREEGENERATOR_H

#include "src/classes/environment/vertex.h"
#include <QPointF>
#include <cmath>

class Session;

class TreeGenerator
{
public:
    TreeGenerator(Session* session);
    ~TreeGenerator();
    virtual Vertex* generate();

protected:
    Session* session;
};

#endif // TREEGENERATOR_H
