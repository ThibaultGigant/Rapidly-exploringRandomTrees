#ifndef HEIGHTMAPFILEPANEL_H
#define HEIGHTMAPFILEPANEL_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include "src/app/heightmappanel/heightmapviewpanel.h"

class CentralWidget;

class HeightMapFilePanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFilePanel(CentralWidget *centralWidget, HeightMapViewPanel *viewPanel, QWidget *parent = 0);


private:
    CentralWidget *cw;
    QHBoxLayout *layout;

    QPushButton *saveButton;
    QPushButton *newButton;
    QPushButton *loadButton;
    QPushButton *clearButton;

    QLabel *mapName;
    QLabel *mapWidth;
    QLabel *mapHeight;


signals:

    void sendClearImage(int count);

public slots:

    void receiveClickClear();
    void saveMap();
    void loadMap();
    void receiveModifAllowed(bool modifAllowed);

};

#endif // HEIGHTMAPFILEPANEL_H
