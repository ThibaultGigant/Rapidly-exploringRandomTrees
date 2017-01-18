#include "heightmapsubpanel.h"
#include "src/app/centralwidget.h"

HeightMapSubPanel::HeightMapSubPanel(CentralWidget *centralWidget, HeightMapViewPanel *viewPanel,QWidget *parent) :
    QWidget(parent)
{

    eraseMode = false;

    this->centralWidget = centralWidget;
    this->viewPanel = viewPanel;

    increaseButton = new QPushButton(" + ");
    size = new QLabel(QString::number(viewPanel->getPenSize()));
    decreaseButton = new QPushButton(" - ");
    eraserButton = new QPushButton("Erase");
    saveImageButton = new QPushButton("Save Image");


    layout = new QHBoxLayout();

    layout->setAlignment(Qt::AlignLeft);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    QLabel *penSize = new QLabel("Pen Size : ");

    layout->addWidget(penSize);
    layout->addWidget(increaseButton);
    layout->addWidget(size);
    layout->addWidget(decreaseButton);
    layout->addWidget(eraserButton);
    layout->addWidget(saveImageButton);

    this->setLayout(layout);

    connect(increaseButton,SIGNAL(clicked(bool)),this->viewPanel,SLOT(increasePenSize()));
    connect(decreaseButton,SIGNAL(clicked(bool)),this->viewPanel,SLOT(decreasePenSize()));

    connect(eraserButton,SIGNAL(clicked(bool)),this, SLOT(toggleMode()));
    connect(this,SIGNAL(toggleModeSig()), this->viewPanel,SLOT(toggleMode()));
    connect(saveImageButton, SIGNAL(clicked(bool)),this, SLOT(saveImageSlot()));

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
    saveImageButton->setEnabled(isModifAllowed);
}

void HeightMapSubPanel::toggleMode(){
    eraseMode = !eraseMode;
    eraserButton->setText( (eraseMode)?"Draw":"Erase");
    emit toggleModeSig();
}

void HeightMapSubPanel::saveImageSlot(){

    QString path = QFileDialog::getSaveFileName(this, tr("Save Height Map"), QDir::homePath()+"/view.png", tr("PNG (*.png)"));
    if(path != Q_NULLPTR){
        this->viewPanel->getView().save(path);
    }
}



