#include "heightmapsubpanel.h"
#include "src/app/centralwidget.h"

HeightMapSubPanel::HeightMapSubPanel(CentralWidget *centralWidget, HeightMapViewPanel *viewPanel,QWidget *parent) :
    QWidget(parent)
{
    this->centralWidget = centralWidget;
    this->viewPanel = viewPanel;

    increaseButton = new QPushButton(" + ");
    size = new QLabel(QString::number(viewPanel->getPenSize()));
    decreaseButton = new QPushButton(" - ");
    eraserButton = new QPushButton("Eraser");

    layout = new QHBoxLayout();

    layout->setAlignment(Qt::AlignLeft);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    layout->addWidget(increaseButton);
    layout->addWidget(size);
    layout->addWidget(decreaseButton);
    layout->addWidget(eraserButton);

    this->setLayout(layout);

    connect(increaseButton,SIGNAL(clicked(bool)),this->viewPanel,SLOT(increasePenSize()));
    connect(decreaseButton,SIGNAL(clicked(bool)),this->viewPanel,SLOT(decreasePenSize()));
    connect(this->viewPanel,SIGNAL(sendPenSize(int)),this,SLOT(majSizeLabel(int)));
    connect(viewPanel,SIGNAL(sendModifAllowed(bool)),this,SLOT(receiveModifAllowed(bool)));
}

void HeightMapSubPanel::majSizeLabel(int s){
    size->setText(QString::number(s));
}

void HeightMapSubPanel::receiveModifAllowed(bool isModifAllowed){
    increaseButton->setEnabled(isModifAllowed);
    decreaseButton->setEnabled(isModifAllowed);
    eraserButton->setEnabled(isModifAllowed);
}
