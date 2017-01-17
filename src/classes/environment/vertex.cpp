#include "vertex.h"



int Vertex::idCount;


/**
 * @brief Constructor
 * @param position Vertex's Position in the environment
 * @param parent Vertex's parent in the tree
 */
Vertex::Vertex(QPointF position, Vertex* parent)
{
    this->parent = parent;
    this->position = position;
    this->children = QVector<Vertex*>();

    if (parent)
    {
        parent->addChild(this);
        this->connectedComponentPointer = this->parent->connectedComponentPointer;
    }
    else
    {
        this->connectedComponentPointer = this;
    }

    this->id = getUniqueId();
}

/**
 * @brief Vertex::~Vertex Destructor
 */
Vertex::~Vertex()
{
    this->children.clear();
}

/**
 * @brief Getter of the position
 * @return Vertex's position
 */
QPointF Vertex::getPosition()
{
    return this->position;
}

/**
 * @brief Getter of the parent
 * @return Parent du sommet dans l'arbre
 */
Vertex* Vertex::getParent()
{
    return this->parent;
}

/**
 * @brief Adds a child to the vertex
 * @param child Child vertex to add
 */
void Vertex::addChild(Vertex *child)
{
    this->children.append(child);
}

/**
 * @brief Returns the list of children of the vertex
 * @return List of children
 */
QVector<Vertex *> Vertex::getChildren() const
{
    return children;
}

/**
 * @brief Vertex::getId
 * @return Returns the id of the vertex
 */
int Vertex::getId(){
    return id;
}

/**
 * @brief Sets the pointer to the new connected component marker
 * @param vertex Vertex that is the origin of the connected component
 */
void Vertex::setConnectedComponentPointer(Vertex *vertex)
{
    Vertex* temp;

    // If the marker is the same, then no change is needed
    if (this->connectedComponentPointer == vertex)
        return;

    // Else we have to change it and tell all of the connected vertices to do the same
    this->connectedComponentPointer = vertex;
    if (parent)
        this->parent->setConnectedComponentPointer(vertex);
    foreach (temp, this->getChildren()) {
        temp->setConnectedComponentPointer(vertex);
    }
}

/**
 * @brief Returns the pointer of the root of the connected component
 * @return Pointer of the root
 */
Vertex *Vertex::getConnectedComponentPointer() const
{
    return connectedComponentPointer;
}

/**
 * @brief Vertex::toString
 * @return A QString representing the Vertes [ id x y parentId childrenIds ]
 */
QString Vertex::toString(){
    QString res =  "";

    res += QString::number(id) + " " + QString::number(position.x()) +" "+QString::number(position.y())+" ";
    res+= (parent)?(QString::number(parent->getId())+" "):"";

    for(int i = 0;i<children.length();i++){
        res+=QString::number(children[i]->getId())+" ";
    }
    return res;
}

/**
 * @brief Vertex::getUniqueId
 * @return return an id for a vertex
 */
int Vertex::getUniqueId(){
    return idCount++;
}

/**
 * @brief Resets the id counter to 0
 */
void Vertex::resetVertexId(){
    idCount = 0;
}


