#include "environment.h"

/**
 * @brief Constructor
 * @param width Environment's width
 * @param height Environment's height
 * @param vertex Starting Vertex of the tree
 */
Environment::Environment(int width, int height,Vertex* vertex)
{
    // Initialization of attributes
    this->width = width;
    this->height = height;
    this->startVertex = vertex;

    // Initialization of the quadrants
    for (int colonne = 0; colonne < height; colonne++)
    {
        QVector<Quadrant> vecColonne;
        this->quadrants.append(vecColonne);
        for (int ligne = 0; ligne < height; ligne++)
        {
            this->quadrants[colonne].append(Quadrant());
        }
    }

    // Adding the starting vertex to the right quadrant
    addElement(vertex);
}

/**
 * @brief Destructor
 */
Environment::~Environment()
{
}

/**
 * @brief Add a vertex to the quadrants he's in
 * @param vertex Vertex to add
 */
void Environment::addElement(Vertex *vertex)
{
    int ligne;
    int colonne;
    QPointF p = vertex->getPosition();
    ligne = (int) (p.x() / width);
    colonne = (int) (p.y() / height);

    this->quadrants[colonne][ligne].addVertex(vertex);
}

/**
 * @brief Return the closest vertex of a given point
 * @param point Point of the environment
 * @return Closest vertex of the given point
 */
Vertex* Environment::getClosest(QPointF point)
{
    //TODO
}


