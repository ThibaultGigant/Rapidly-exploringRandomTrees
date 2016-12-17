#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent, Config *config) : QWidget(parent)
{

    this->config = config;
    layout = new QHBoxLayout;
    hmFrame = new HeightMapFrame(this,config);
    this->configPanel = new ConfigPanel(this);

    layout->addWidget(hmFrame);
    layout->addWidget(this->configPanel);
    setLayout(layout);

}
