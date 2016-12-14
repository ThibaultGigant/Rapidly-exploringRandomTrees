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
    ligne = (int) (p.x() / this->width) * this->session->getDeltaT();
    colonne = (int) (p.y() / this->height) * this->session->getDeltaT();

    this->quadrants[colonne][ligne].addVertex(vertex);
}

/**
 * @brief Returns the closest vertex of a given point
 * @param point Point of the environment
 * @return Closest vertex of the given point
 */
Vertex* Environment::getClosest(QPointF point)
{
    // Initialization of variables
    double minDistance = width + height;
    double tempDistance;
    Vertex* vertex;
    int pointLine = (int) (point.y() / height);
    int pointColumn = (int) (point.x() / width);
    bool flag = false;
    QVector<Vertex*> vertices;

    // Determination of how many quadrants separate the point and it's closest vertex
    int i = 0;
    while (i < std::max(this->nbLines, this->nbColumns))
    {
        // Verification on the 4 quadrants above, under, on the right and on the left, separated by i quadrants from the point's quadrant
        if (( pointLine - i > 0 && !this->quadrants[pointColumn][pointLine - i].getVertices().isEmpty()) ||
                (pointLine + i < nbLines && !this->quadrants[pointColumn][pointLine + i].getVertices().isEmpty()) ||
                (pointColumn - i > 0 && !this->quadrants[pointColumn - i][pointLine].getVertices().isEmpty()) ||
                (pointColumn + i < nbColumns && !this->quadrants[pointColumn + i][pointLine].getVertices().isEmpty()))
            break;

        // Verification of all other quadrants separated by i quadrants from the point's quadrant
        for (int j = 1; j <= i; j++)
        {
            // Verification above and under
            if (( pointLine - i > 0 && pointColumn - j > 0 && !this->quadrants[pointColumn - j][pointLine - i].getVertices().isEmpty()) ||
                    ( pointLine + i < nbLines && pointColumn - j > 0 && !this->quadrants[pointColumn - j][pointLine + i].getVertices().isEmpty()) ||
                    ( pointLine - i > 0 && pointColumn + j < nbColumns && !this->quadrants[pointColumn + j][pointLine - i].getVertices().isEmpty()) ||
                    ( pointLine + i < nbLines && pointColumn + j < nbColumns && !this->quadrants[pointColumn + j][pointLine + i].getVertices().isEmpty()))
            {
                flag = true;
                break;
            }

            // Verification on the left and on the right
            if (( pointLine - j > 0 && pointColumn - i > 0 && !this->quadrants[pointColumn - i][pointLine - j].getVertices().isEmpty()) ||
                    ( pointLine + j < nbLines && pointColumn - i > 0 && !this->quadrants[pointColumn - i][pointLine + j].getVertices().isEmpty()) ||
                    ( pointLine - j > 0 && pointColumn + i < nbColumns && !this->quadrants[pointColumn + i][pointLine - j].getVertices().isEmpty()) ||
                    ( pointLine + j < nbLines && pointColumn + i < nbColumns && !this->quadrants[pointColumn + i][pointLine + j].getVertices().isEmpty()))
            {
                flag = true;
                break;
            }

            if (flag)
                break;
        }
        i++;
    }

    // Closest Vertex in the square limited by i
    for (int j = 0; j <= i; j++)
    {
        // Verification above and on the left
        if (( pointLine - i > 0 && pointColumn - j > 0 && !this->quadrants[pointColumn - j][pointLine - i].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn - j][pointLine - i].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification above and on the right
        if ((i != 0 && j != 0 && pointLine - i > 0 && pointColumn + j < nbColumns && !this->quadrants[pointColumn + j][pointLine - i].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn + j][pointLine - i].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification under and on the left
        if ((i != 0 && pointLine + i < nbLines && pointColumn - j > 0 && !this->quadrants[pointColumn - j][pointLine + i].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn - j][pointLine + i].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification under and on the right
        if ((i != 0 && j != 0 && pointLine + i < nbLines && pointColumn + j < nbColumns && !this->quadrants[pointColumn + j][pointLine + i].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn + j][pointLine + i].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification on the left and up
        if ((i != 0 && j < i && pointLine - j > 0 && pointColumn - i > 0 && !this->quadrants[pointColumn - i][pointLine - j].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn - i][pointLine - j].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification on the right and up
        if ((i != 0 && j < i && j != 0 && pointLine - j > 0 && pointColumn + i < nbColumns && !this->quadrants[pointColumn + i][pointLine - j].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn + i][pointLine - j].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification on the left and down
        if ((i != 0 && j < i && pointLine + j < nbLines && pointColumn - i > 0 && !this->quadrants[pointColumn - i][pointLine + j].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn - i][pointLine + j].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

        // Verification on the right and down
        if ((i != 0 && j < i && j != 0 && pointLine + j < nbLines && pointColumn + i < nbColumns && !this->quadrants[pointColumn + i][pointLine + j].getVertices().isEmpty()))
        {
            vertices = this->quadrants[pointColumn + i][pointLine + j].getVertices();
            for (int k = 0; k < vertices.size(); k++)
            {
                tempDistance = this->session->getMetric()->distance(vertices[k]->getPosition(), point) < minDistance;
                if (tempDistance < minDistance)
                {
                    minDistance = tempDistance;
                    vertex = vertices[k];
                }
            }
        }

    }

    return vertex;
}

/**
 * @brief Returns the closest vertex of a given point, by going through all of the vertices in the environment
 * @param point Point of the environment
 * @return Closest vertex of the given point
 */
Vertex* Environment::getClosestNaive(QPointF point)
{
    // Initialization of variables
    double minDistance = width + height;
    double tempDistance;
    Vertex* vertex, *tempVertex;
    qDebug() << "entrée getclosest";
    qDebug() << this->quadrants.size();

    // Going through every vertex of every quadrant
    for (int i = 0; i < this->quadrants.size(); i++)
    {
        qDebug() << "debug i";
        for (int j = 0; j < this->quadrants[i].size(); j++)
        {
            qDebug() << "debug j";
            for (int k = 0; k < this->quadrants[i][j].getVertices().size(); k++)
            {
                qDebug() << "debug k";
                tempVertex = this->quadrants[i][j].getVertices()[k];
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
 * @brief Returns a random vertex of the tree
 * @return Random Vertex
 */
Vertex* Environment::getRandomVertex()
{
    int line = rand() % this->nbLines;
    int column = rand() % this->nbColumns;
    QVector<Vertex*> vertices = this->quadrants[column][line].getVertices();
    int elementIndex = rand() % vertices.size();
    return vertices[elementIndex];
}
