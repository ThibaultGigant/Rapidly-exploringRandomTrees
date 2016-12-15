#include "heightmapframe.h"

HeightMapFrame::HeightMapFrame(QWidget *parent, Config * config) :
    QWidget(parent)
{

    this->config = config;

    layout = new QVBoxLayout;

    // Creating file Panel (Top)
    hmFilePanel = new HeightMapFilePanel(this,config);
    hmFilePanel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    // Creating view Panel (Middle)
    hmViewPanel = new HeightMapViewPanel(this,config);

    viewScroller = new QScrollArea;
    viewScroller->setBackgroundRole(QPalette::Dark);

    QSize AdjustSize = hmViewPanel->size();
    AdjustSize.setWidth(config->WIDTH);
    AdjustSize.setHeight(config->HEIGHT);
    qDebug() << AdjustSize.width();


    hmViewPanel->setMinimumSize(AdjustSize);
    hmViewPanel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    viewScroller->setWidget(hmViewPanel);
    viewScroller->ensureWidgetVisible(hmViewPanel,hmViewPanel->width(),hmViewPanel->height());
    viewScroller->setWidgetResizable(true);
    viewScroller->setMaximumWidth(config->WIDTH);
    viewScroller->setMaximumHeight(config->HEIGHT);

    // Creating Pen Panel (Bottom)
    //hmSubPanel = new HeightMapSubPanel;




    // Adding all widgets
    layout->addWidget(hmFilePanel);
    layout->addWidget(viewScroller);
    //layout->addWidget(hmSubPanel);

    this->setLayout(layout);
}
