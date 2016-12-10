#ifndef TREEGENERATOR_H
#define TREEGENERATOR_H

#include "src/classes/environment/vertex.h"

class Session;

class TreeGenerator
{
public:
    TreeGenerator(Session* session);
    ~TreeGenerator();
    virtual Vertex generate();

private:
    Session* session;
};

#endif // TREEGENERATOR_H
