#include "vertex.h"

/**
 * @brief Vertex::Vertex Constructeur
 * @param position Position du Sommet dans l'espace
 * @param parent Sommet parent dans l'arbre
 */
Vertex::Vertex(vector<double> position, Vertex* parent)
{
    this->parent = parent;
    this->position = position;
}

/**
 * @brief Vertex::~Vertex Destructeur
 */
Vertex::~Vertex()
{
}

/**
 * @brief Vertex::getPosition Getter de la position
 * @return Position du Sommet
 */
vector<double> Vertex::getPosition()
{
    return this->position;
}

/**
 * @brief Vertex::getParent Getter du parent
 * @return Parent du sommet dans l'arbre
 */
Vertex* Vertex::getParent()
{
    return this->parent;
}
