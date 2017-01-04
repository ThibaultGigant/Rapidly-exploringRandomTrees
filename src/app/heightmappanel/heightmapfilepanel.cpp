#include "heightmapfilepanel.h"
#include "src/app/centralwidget.h"

HeightMapFilePanel::HeightMapFilePanel(CentralWidget *centralWidget, HeightMapViewPanel* viewPanel, QWidget *parent) :
    QWidget(parent)
{
    // Variables initialization
    this->cw = centralWidget;

    layout = new QHBoxLayout;

    mapName = new QLabel(cw->getCurrentMap()->getName());
    mapWidth = new QLabel(QString::number(cw->getCurrentMap()->getWidth()));
    mapHeight = new QLabel(QString::number(cw->getCurrentMap()->getHeight()));

    saveButton = new QPushButton("Save");
    newButton = new QPushButton("New");
    loadButton = new QPushButton("Load");
    clearButton = new QPushButton("Clear");

    // Interface Construction

    layout->setAlignment(Qt::AlignLeft);

    layout->addWidget(mapName);
    layout->addWidget(mapWidth);
    layout->addWidget(mapHeight);

    layout->addWidget(saveButton);
    layout->addWidget(newButton);
    layout->addWidget(loadButton);
    layout->addWidget(clearButton);

    setLayout(layout);

    // Connexions

    connect(clearButton,SIGNAL(clicked(bool)),this,SLOT(receiveClickClear()));
    connect(this,SIGNAL(sendClearImage(int)),cw,SLOT(receiveClearImage(int)));


    connect(saveButton,SIGNAL(clicked(bool)),cw,SLOT(receiveImageToHeightMap()));
    connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(saveMap()));

    connect(loadButton,SIGNAL(clicked(bool)),this,SLOT(loadMap()));

    connect(viewPanel,SIGNAL(sendModifAllowed(bool)),this,SLOT(receiveModifAllowed(bool)));


    connect(newButton,SIGNAL(clicked(bool)),this,SLOT(newMap()));

}

void HeightMapFilePanel::receiveClickClear(){
    emit sendClearImage(0);
}

void HeightMapFilePanel::saveMap(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Height Map"), cw->getCurrentMap()->getName(), tr("HeightMapFile (*.hmf)"));

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to save file"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    out << cw->getCurrentMap()->toFileString();
    file.close();

}

void HeightMapFilePanel::loadMap(){

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Height Map"), tr("HeightMapFile (*.hmf)"));

    qDebug() << "map received : " << fileName;

    HeightMap * newMap = HeightMap::hmFromFile(fileName);

    if (newMap != Q_NULLPTR){
        delete(cw->getCurrentMap());
        cw->setCurrentMap(newMap);
        emit sendClearImage(0);
    }else{
        QMessageBox::information(this, tr("Unable to open file"),"Something bad happened :(");
    }

}

void HeightMapFilePanel::newMap(){
    cw->getCurrentMap()->clearMap();
    emit sendClearImage(0);
}


void HeightMapFilePanel::receiveModifAllowed(bool modifAllowed){
    saveButton->setEnabled(modifAllowed);
    newButton->setEnabled(modifAllowed);
    loadButton->setEnabled(modifAllowed);
    clearButton->setEnabled(modifAllowed);
}



