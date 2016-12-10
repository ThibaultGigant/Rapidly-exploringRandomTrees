#ifndef QUADRANT_H
#define QUADRANT_H

#include <vector>
#include "vertex.h"
using namespace std;

class Quadrant
{
public:
    Quadrant();
    ~Quadrant();
    void addVertex(Vertex* vertex);
    vector<Vertex*>* getVertices();

private:
    vector<Vertex*> vertices;
};

#endif // QUADRANT_H
