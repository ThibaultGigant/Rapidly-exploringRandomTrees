#include "heightmapsuppanel.h"

HeightMapSupPanel::HeightMapSupPanel(QWidget *parent, HeightMap * map) :
    QWidget(parent)
{

    this->map = map;

    this->saveButton = QPushButton("Save",this);
    newButton = QPushButton("New",this);
    loadButton = QPushButton("Load",this);
    deleteButton = QPushButton("Del",this);



}
