#ifndef TREEGENERATOR_H
#define TREEGENERATOR_H

#include "src/classes/environment/vertex.h"
#include <QPointF>
#include <cmath>

class Session;

class TreeGenerator
{
public:
    TreeGenerator();
    ~TreeGenerator();
    virtual Vertex* generate();

    Session *getSession() const;
    void setSession(Session *value);

protected:
    Session* session;
};

#endif // TREEGENERATOR_H
