#include "environnement.h"

Environnement::Environnement(int width, int height,Vertex* vertex)
{
    this->startVertex = vertex;
    //this->quadrants
    for (int ligne = 0; ligne < width; ligne++)
    {
        vector<Quadrant> vecLigne;
        this->quadrants.push_back(vecLigne);
        for (int colonne = 0; colonne < height; colonne++)
        {
            this->quadrants[ligne].push_back(Quadrant());
        }
    }
}
