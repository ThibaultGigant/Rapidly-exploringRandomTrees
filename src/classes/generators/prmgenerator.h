#ifndef PRMGENERATOR_H
#define PRMGENERATOR_H

#include "treegenerator.h"

class PRMGenerator : public TreeGenerator
{
public:
    PRMGenerator(int nbToExamine = INFINITY);
    ~PRMGenerator();
    virtual Vertex* generate();
    virtual QString toString();

private:
    /**
     * @brief nbToExamine Number of closest vertices to examine on every generation
     */
    int nbToExamine;
};

#endif // PRMGENERATOR_H
