#include "heightmapframe.h"

HeightMapFrame::HeightMapFrame(QWidget *parent, Config * config) :
    QWidget(parent)
{

    this->config = config;

    layout = new QVBoxLayout;
    //hmFilePanel = new HeightMapFilePanel(this,config);
    hmViewPanel = new HeightMapViewPanel(this,config);
    //hmSubPanel = new HeightMapSubPanel;


    //layout->addWidget(hmFilePanel);
    layout->addWidget(hmViewPanel);
    //layout->addWidget(hmSubPanel);

    this->setLayout(layout);
}
