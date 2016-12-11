#ifndef RANDOMTREEGENERATOR_H
#define RANDOMTREEGENERATOR_H

#include "treegenerator.h"
#include <cmath>

class RandomTreeGenerator : public TreeGenerator
{
public:
    RandomTreeGenerator(Session* session);
    ~RandomTreeGenerator();
    virtual Vertex* generate();
};

#endif // RANDOMTREEGENERATOR_H
