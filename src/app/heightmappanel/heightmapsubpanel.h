#ifndef HEIGHTMAPSUBPANEL_H
#define HEIGHTMAPSUBPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
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
    QPushButton *eraserButton;
    QPushButton *saveImageButton;

    QHBoxLayout *layout;

   bool eraseMode;


signals:
    void increasePenSize();
    void decreasePenSize();
    void toggleModeSig();

public slots:

    void majSizeLabel(int s);
    void receiveModifAllowed(bool isModifAllowed);
    void toggleMode();
    void saveImageSlot();
};

#endif // HEIGHTMAPSUBPANEL_H
