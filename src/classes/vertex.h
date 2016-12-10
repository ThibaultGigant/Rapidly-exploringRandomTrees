#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class Vertex
{

public:
    Vertex(vector<double> position, Vertex* parent);
    ~Vertex();
    vector<double> getPosition();
    Vertex* getParent();

private:
    vector<double> position;
    Vertex* parent;

};

#endif // VERTEX_H
