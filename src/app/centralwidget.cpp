#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent, Config *config) : QWidget(parent)
{

    this->config = config;
    layout = new QHBoxLayout;
    hmFrame = new HeightMapFrame(this,config);
    layout->addWidget(hmFrame);
    setLayout(layout);

}
