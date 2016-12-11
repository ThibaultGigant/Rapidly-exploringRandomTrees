#ifndef HEIGHTMAPSUPPANEL_H
#define HEIGHTMAPSUPPANEL_H

#include <QWidget>
#include <QPushButton>
#include "../classes/heightmap.h"


class HeightMapSupPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapSupPanel(QWidget *parent = 0, HeightMap * map = 0);

private :

    HeightMap * map;

    QPushButton mapName;
    QPushButton mapWidth;
    QPushButton mapHeight;

    QPushButton saveButton;
    QPushButton newButton;
    QPushButton loadButton;
    QPushButton deleteButton;



signals:

public slots:


};

#endif // HEIGHTMAPSUPPANEL_H
