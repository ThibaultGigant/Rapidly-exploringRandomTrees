#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <vector>
#include "vertex.h"
#include "quadrant.h"

class Environnement
{
public:
    Environnement(int width, int height,Vertex* vertex);
    ~Environnement();

private:
    Vertex* startVertex;
    vector<vector<Quadrant> > quadrants;
};

#endif // ENVIRONNEMENT_H
