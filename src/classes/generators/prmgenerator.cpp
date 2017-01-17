#include "prmgenerator.h"
#include "src/classes/session.h"
#include "src/classes/environment/vertex.h"
#include <QDebug>

/**
 * @brief Constructor
 * @param nbToExamine Number of closest vertices to examine on every generation
 */
PRMGenerator::PRMGenerator(int nbToExamine) : TreeGenerator()
{
    this->nbToExamine = nbToExamine;
}

/**
 * @brief Destructor
 */
PRMGenerator::~PRMGenerator()
{

}

/**
 * @brief Generates a new vertex according to the PRM (Probabilistic RoadMap) algorithm
 * @return New Vertex generated, to be added
 */
Vertex* PRMGenerator::generate()
{
    Vertex *vertex, *tempVertex;
    double newX, newY;
    QPointF point;

    // Determining a random point that is not an obstacle
    do
    {
        newX = (rand() / (double) RAND_MAX) * this->session->getWidth();
        newY = (rand() / (double) RAND_MAX) * this->session->getHeight();
        point = QPointF(newX, newY);
    } while (this->session->isObstacle(point));

    // Finding the k vertices reachable from the point
    QVector<Vertex*> kReachables = this->session->getKReachableClosest(point, this->nbToExamine);

    // Generating the vertex to add
    if (kReachables.isEmpty())
    {
       return new Vertex(point, NULL);
    }

    //qDebug() << "PRMGenerator ==> We have found reachable points : " << kReachables.size();

    vertex = new Vertex(point, kReachables.first());

    for(int i = 1; i < kReachables.size(); i++) {
        tempVertex = kReachables.at(i);
        tempVertex->setConnectedComponentPointer(vertex->getConnectedComponentPointer());
        tempVertex->addChild(vertex);
        vertex->addChild(tempVertex);
    }

    return vertex;
}

/**
 * @brief Displays the type of algorithm used for the generation of the tree
 * @return String of the generation algorithm
 */
QString PRMGenerator::toString()
{
    return "Probabilistic RoadMap (PRM) Algorithm";
}

/**
 * @brief Getter of the number of closest vertices to examine on every generation
 * @return This number
 */
int PRMGenerator::getNbToExamine() const
{
    return nbToExamine;
}

/**
 * @brief Setter of the number of closest vertices to examine on every generation
 * @param value New vqlue of this number
 */
void PRMGenerator::setNbToExamine(int value)
{
    nbToExamine = value;
}
