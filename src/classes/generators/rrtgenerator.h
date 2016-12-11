#ifndef RRTGENERATOR_H
#define RRTGENERATOR_H

#include "treegenerator.h"

class RRTGenerator : public TreeGenerator
{
public:
    RRTGenerator(Session* session);
    ~RRTGenerator();
    virtual Vertex* generate();
};

#endif // RRTGENERATOR_H
