#ifndef RRTGENERATOR_H
#define RRTGENERATOR_H

#include "treegenerator.h"

class RRTGenerator : public TreeGenerator
{
public:
    RRTGenerator();
    ~RRTGenerator();
    virtual Vertex* generate();
    virtual QString toString();
};

#endif // RRTGENERATOR_H
