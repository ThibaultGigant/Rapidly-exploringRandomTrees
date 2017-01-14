#include "environment.h"
#include "src/classes/metrics/metric.h"
#include <QDebug>

/**
 * @brief Constructor
 * @param session Session creating the environment
 * @param width Environment's width
 * @param height Environment's height
 * @param vertex Starting Vertex of the tree
 */
Environment::Environment(Session* session, int width, int height,Vertex* vertex)
{
    // Initialization of attributes
    this->session = session;
    this->startVertex = vertex;
    this->width = width;
    this->height = height;
    // nbLines and nbColumns are calculated so each quadrant's side should have a length of delta_t
    this->nbLines = ceil(height/this->session->getDeltaT());
    this->nbColumns = ceil(width/this->session->getDeltaT());
    this->vertices = QVector<Vertex *>();

    this->quadrants = QVector<QVector<Quadrant> >();

    // Initialization of the quadrants
    for (int colonne = 0; colonne < this->nbColumns; colonne++)
    {
        QVector<Quadrant> vecColonne;
        this->quadrants.append(vecColonne);
        for (int ligne = 0; ligne < this->nbLines; ligne++)
        {
            this->quadrants.last().append(Quadrant());
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
    Vertex *vertex;
    foreach (vertex, this->vertices) {
        delete vertex;
    }
    this->quadrants.clear();
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
    colonne = (int) (p.x() / this->width) * this->session->getDeltaT();
    ligne = (int) (p.y() / this->height) * this->session->getDeltaT();

    // Add the vertex to the right quadrant and the set of all vertices
    this->quadrants[colonne][ligne].addVertex(vertex);
    this->vertices.append(vertex);
}

/**
 * @brief Returns the closest vertex of a given point in the 9 quadrants around the point (the one it's in, and the 8 surrounding)
 * @param point Point of the environment
 * @return Closest vertex of the given point in those 9 quadrants if it exists, null otherwise
 */
Vertex* Environment::getClosestAround(QPointF point, int radius)
{
    // Initialization of variables
    double minDistance = INFINITY;
    double tempDistance;
    Vertex* vertex, *tempVertex;
    int ligne;
    int colonne;

    colonne = (int) (point.x() / this->width) * this->session->getDeltaT();
    ligne = (int) (point.y() / this->height) * this->session->getDeltaT();

    for (int i = std::max(colonne - radius, 0); i < std::min(colonne + radius, this->nbColumns); i++)
    {
        for (int j = std::max(ligne - radius, 0); j < std::min(ligne + radius, this->nbLines); j++)
        {
            foreach (tempVertex, this->quadrants[i][j].getVertices()) {
                tempDistance = this->session->distance(point, tempVertex->getPosition());
                // Change the closest vertex if applicable
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = tempVertex;
                }
            }
        }
    }

    return vertex;
}

/**
 * @brief Returns the closest vertex of a given point
 * @param point Point of the environment
 * @return Closest vertex of the given point
 */
Vertex* Environment::getClosest(QPointF point)
{
    // Initialization of variables
    bool flag = false;
    int colonne = (int) (point.x() / this->width) * this->session->getDeltaT();
    int ligne = (int) (point.y() / this->height) * this->session->getDeltaT();

    for (int i = std::max(colonne - 1, 0); i < std::min(colonne + 1, this->nbColumns); i++)
    {
        for (int j = std::max(ligne - 1, 0); j < std::min(ligne + 1, this->nbLines); j++)
        {
            if (!this->quadrants[i][j].getVertices().isEmpty())
            {
                flag = true;
                break;
            }
        }
    }

    // If there are no vertices around, check everywhere
    if (!flag)
        return this->getClosestNaive(point);

    return this->getClosestAround(point, 2);
}

/**
 * @brief Returns the closest vertex of a given point, by checking the nearest quadrants, and if empty, all quadrants (naive)
 * @param point Point of the environment
 * @return Closest vertex of the given point
 */
Vertex* Environment::getClosestAlmostNaive(QPointF point)
{
    // Initialization of variables
    int ligne;
    int colonne;
    colonne = (int) (point.x() / this->width) * this->session->getDeltaT();
    ligne = (int) (point.y() / this->height) * this->session->getDeltaT();

    if (this->quadrants[colonne][ligne].getVertices().isEmpty())
        return this->getClosestNaive(point);

    return this->getClosestAround(point, 1);
}

/**
 * @brief Returns the closest vertex of a given point, by going through all of the vertices in the environment
 * @param point Point of the environment
 * @return Closest vertex of the given point
 */
Vertex* Environment::getClosestNaive(QPointF point)
{
    // Initialization of variables
    double minDistance = INFINITY;
    double tempDistance;
    Vertex* vertex, *tempVertex;

    // Going through every vertex
    foreach (tempVertex, this->vertices) {
        tempDistance = this->session->distance(point, tempVertex->getPosition());
        // Change the closest vertex if applicable
        if (tempDistance < minDistance)
        {
            minDistance = tempDistance;
            vertex = tempVertex;
        }
    }

    return vertex;
}

/**
 * @brief Finds the k closest vertices of a point that are reachable (no obstacle on the path) and not in the same connected component
 * @param point Point of
 * @param k
 * @return
 */
QVector<Vertex *> Environment::getKReachableClosest(QPointF point, int k)
{
    QVector<Vertex*> kReachable;
    QVector<double> kDistances;

    // Initialization of variables
    double tempDistance;
    Vertex *tempVertex;
    int ligne;
    int colonne;
    int index, indexSame;

    // Calculates the coordinates of the quadrant the vertex is in
    colonne = (int) (point.x() / this->width) * this->session->getDeltaT();
    ligne = (int) (point.y() / this->height) * this->session->getDeltaT();

    // Looking every quadrant within delta_t distance to find the k reachable vertices from the point
    for (int i = std::max(colonne - 1, 0); i < std::min(colonne + 1, this->nbColumns); i++)
    {
        for (int j = std::max(ligne - 1, 0); j < std::min(ligne + 1, this->nbLines); j++)
        {
            foreach (tempVertex, this->quadrants[i][j].getVertices()) {
                tempDistance = this->session->distance(point, tempVertex->getPosition());
                // Adds the vertex to the list if necessary
                if (tempDistance <= this->session->getDeltaT())
                {
                    if (this->session->isPathFree(point, tempVertex->getPosition()))
                    {
                        index = k;
                        indexSame = k;
                        // Getting the index where we should put the vertex
                        for (int m = 0; m < kDistances.size(); m++)
                        {
                            if (tempDistance < kDistances.at(m))
                                index = m;
                            if (tempVertex->getConnectedComponentPointer() == kReachable.at(m)->getConnectedComponentPointer())
                                indexSame = m;
                        }
                        if (index < indexSame)
                        {
                            kReachable.insert(index, tempVertex);
                            kDistances.insert(index, tempDistance);
                            if (kDistances.size() > k)
                            {
                                kReachable.removeLast();
                                kDistances.removeLast();
                            }
                        }
                    }
                }
            }
        }
    }

    return kReachable;
}



/**
 * @brief Returns a random vertex of the tree
 * @return Random Vertex
 */
Vertex* Environment::getRandomVertex()
{
    int elementIndex = rand() % this->vertices.size();
    return this->vertices[elementIndex];
}

/**
 * @brief Getter of the vertices in the environment
 * @return A vector of vertices
 */
QVector<Vertex *> Environment::getVertices() const
{
    return vertices;
}

/**
 * @brief Sets the vertices of the environment
 * @param value A vector of vertices
 */
void Environment::setVertices(const QVector<Vertex *> &value)
{
    vertices = value;
}

QString Environment::toString(){
    QString res = "";
    res+=vertices.length()+"\n";
    int edgeCount = 0;

    QString vs = "";
    QString edges = "";

   for(int i = 0; i < vertices.length();i++){

       Vertex *v = vertices[i];

   }



   }


}
















