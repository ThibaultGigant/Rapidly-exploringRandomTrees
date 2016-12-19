#ifndef HEIGHTMAPSUBPANEL_H
#define HEIGHTMAPSUBPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "src/app/heightmappanel/heightmapviewpanel.h"

class CentralWidget;

class HeightMapSubPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapSubPanel(CentralWidget *centralWidget, HeightMapViewPanel *viewPanel,QWidget *parent = 0);

private:
    CentralWidget *centralWidget;
    HeightMapViewPanel *viewPanel;

    QLabel *size;
    QPushButton *increaseButton;
    QPushButton *decreaseButton;
    QPushButton *eraser;

   QHBoxLayout *layout;



signals:
    void increasePenSize();
    void decreasePenSize();
    void goEraser();

public slots:

    void majSizeLabel(int s);

};

#endif // HEIGHTMAPSUBPANEL_H
