#ifndef HEIGHTMAPFILEPANEL_H
#define HEIGHTMAPFILEPANEL_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "src/classes/config.h"

class HeightMapFilePanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFilePanel(QWidget *parent = 0, Config *config = 0);

private:

    Config *config;

    QHBoxLayout *layout;

    QPushButton *saveButton;
    QPushButton *newButton;
    QPushButton *loadButton;
    QPushButton *deleteButton;

    QLabel *mapName;
    QLabel *mapWidth;
    QLabel *mapHeight;


signals:

public slots:
};

#endif // HEIGHTMAPFILEPANEL_H
