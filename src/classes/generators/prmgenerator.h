#ifndef PRMGENERATOR_H
#define PRMGENERATOR_H

#include "treegenerator.h"

class PRMGenerator : public TreeGenerator
{
public:
    PRMGenerator(int nbToExamine = 10);
    ~PRMGenerator();
    virtual Vertex* generate();
    virtual QString toString();

    int getNbToExamine() const;
    void setNbToExamine(int value);

private:
    /**
     * @brief nbToExamine Number of closest vertices to examine on every generation
     */
    int nbToExamine;
};

#endif // PRMGENERATOR_H
