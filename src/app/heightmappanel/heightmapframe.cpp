#include "heightmapframe.h"
#include "src/app/centralwidget.h"

HeightMapFrame::HeightMapFrame(CentralWidget *centralWidget, QWidget *parent) :
    QWidget(parent)
{
    // Variables initialization
    this->centralWidget = centralWidget;
    layout = new QVBoxLayout();

    // Creating file Panel (Top)
    hmFilePanel = new HeightMapFilePanel(this->centralWidget);
    hmFilePanel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    // Creating view Panel (Middle)
    hmViewPanel = new HeightMapViewPanel(this->centralWidget);

    viewScroller = new QScrollArea();
    viewScroller->setBackgroundRole(QPalette::Dark);

    QSize AdjustSize = hmViewPanel->size();
    AdjustSize.setWidth(this->centralWidget->getCurrentMap()->getWidth());
    AdjustSize.setHeight(this->centralWidget->getCurrentMap()->getHeight());
    qDebug() << AdjustSize.width();


    hmViewPanel->setMinimumSize(AdjustSize);
    hmViewPanel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    viewScroller->setWidget(hmViewPanel);
    viewScroller->ensureWidgetVisible(hmViewPanel,hmViewPanel->width(),hmViewPanel->height());
    viewScroller->setWidgetResizable(true);
    viewScroller->setMaximumWidth(this->centralWidget->getCurrentMap()->getWidth());
    viewScroller->setMaximumHeight(this->centralWidget->getCurrentMap()->getHeight());

    // Creating Pen Panel (Bottom)
    //hmSubPanel = new HeightMapSubPanel;




    // Adding all widgets
    layout->addWidget(hmFilePanel);
    layout->addWidget(viewScroller);
    //layout->addWidget(hmSubPanel);

    this->setLayout(layout);
}

HeightMapViewPanel* HeightMapFrame::getHeightMapViewPanel()
{
    return this->hmViewPanel;
}
