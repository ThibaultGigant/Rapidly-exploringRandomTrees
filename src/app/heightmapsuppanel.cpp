#include "heightmapsuppanel.h"

HeightMapSupPanel::HeightMapSupPanel(QWidget *parent, HeightMap * map) :
    QWidget(parent)
{

    this->map = map;

    QPushButton saveButton("Save",this);
    QPushButton newButton("New",this);
    QPushButton loadButton("Load",this);
    QPushButton deleteButton("Del",this);



}
