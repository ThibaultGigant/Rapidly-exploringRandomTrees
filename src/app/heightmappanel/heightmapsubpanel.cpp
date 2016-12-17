#include "heightmapsubpanel.h"
#include "src/app/centralwidget.h"

HeightMapSubPanel::HeightMapSubPanel(CentralWidget *centralWidget, QWidget *parent) :
    QWidget(parent)
{
    this->centralWidget = centralWidget;
}
