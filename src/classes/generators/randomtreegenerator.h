#ifndef RANDOMTREEGENERATOR_H
#define RANDOMTREEGENERATOR_H

#include "treegenerator.h"

class RandomTreeGenerator : public TreeGenerator
{
public:
    RandomTreeGenerator();
    ~RandomTreeGenerator();
    virtual Vertex* generate();
    virtual QString toString();
};

#endif // RANDOMTREEGENERATOR_H
