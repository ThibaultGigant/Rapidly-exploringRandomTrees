#include "quadrant.h"

/**
 * @brief Quadrant::Quadrant Constructeur
 */
Quadrant::Quadrant()
{
}

/**
 * @brief Quadrant::~Quadrant
 */
Quadrant::~Quadrant()
{
    //for (int i = 0; i < this->vertices.size(); i++)
    for (auto v = this->vertices.begin(); v != this->vertices.end(); ++v)
        free(*v);
    this->vertices.clear();
}

/**
 * @brief Quadrant::addVertex Ajoute un sommet au quadrant
 * @param vertex Sommet à ajouter
 */
void Quadrant::addVertex(Vertex* vertex)
{
    this->vertices.push_back(vertex);
}

/**
 * @brief Quadrant::getVertices Renvoie les sommets du quadrant
 * @return Pointeur vers le vector contenant les sommets du quadrant
 */
vector<Vertex*>* Quadrant::getVertices()
{
    return &(this->vertices);
}
