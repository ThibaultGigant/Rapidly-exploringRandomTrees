#ifndef HEIGHTMAPFRAME_H
#define HEIGHTMAPFRAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSize>
#include <QSizePolicy>
#include "heightmapsubpanel.h"
#include "heightmapviewpanel.h"
#include "heightmapfilepanel.h"
#include "src/classes/config.h"

class CentralWidget;

class HeightMapFrame : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFrame(CentralWidget *centralWidget, QWidget *parent = 0);

private :
    CentralWidget *centralWidget;
    HeightMapSubPanel *hmSubPanel;
    HeightMapViewPanel *hmViewPanel;
    HeightMapFilePanel *hmFilePanel;

    QScrollArea *viewScroller;

    QVBoxLayout *layout;

signals:

};

#endif // HEIGHTMAPFRAME_H
