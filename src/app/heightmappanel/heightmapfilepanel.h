#ifndef HEIGHTMAPFILEPANEL_H
#define HEIGHTMAPFILEPANEL_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class CentralWidget;

class HeightMapFilePanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFilePanel(CentralWidget *centralWidget, QWidget *parent = 0);

private:
    CentralWidget *centralWidget;
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
