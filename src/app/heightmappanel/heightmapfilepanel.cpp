#include "heightmapfilepanel.h"
#include "src/app/centralwidget.h"

HeightMapFilePanel::HeightMapFilePanel(CentralWidget *centralWidget, QWidget *parent) :
    QWidget(parent)
{
    // Variables initialization
    this->centralWidget = centralWidget;

    layout = new QHBoxLayout;

    mapName = new QLabel("Map Name");
    mapWidth = new QLabel("W : 250");
    mapHeight = new QLabel("H : 230");

    saveButton = new QPushButton("Save");
    newButton = new QPushButton("New");
    loadButton = new QPushButton("Load");
    deleteButton = new QPushButton("Del");

    // Interface Construction

    layout->setAlignment(Qt::AlignLeft);

    layout->addWidget(mapName);
    layout->addWidget(mapWidth);
    layout->addWidget(mapHeight);

    layout->addWidget(saveButton);
    layout->addWidget(newButton);
    layout->addWidget(loadButton);
    layout->addWidget(deleteButton);

    setLayout(layout);

    // Connexions

    // Connect Buttons To HeightMap

}
