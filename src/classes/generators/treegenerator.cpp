#include "treegenerator.h"

/**
 * @brief Constructor
 * @param session Session using this generator
 */
TreeGenerator::TreeGenerator(Session* session)
{
    this->session = session;
}

/**
 * @brief Destructor
 */
TreeGenerator::~TreeGenerator()
{}

/**
 * @brief Generates a new vertex according to the wanted strategy
 * @return New Vertex generated, to be added
 */
Vertex* TreeGenerator::generate(){
    return new Vertex(QPointF(0, 0), NULL);
}
