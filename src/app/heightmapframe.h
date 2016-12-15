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
#include "../classes/config.h"

class HeightMapFrame : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFrame(QWidget *parent = 0, Config *config = 0);

private :


    Config *config;


    HeightMapSubPanel *hmSubPanel;
    HeightMapViewPanel *hmViewPanel;
    HeightMapFilePanel *hmFilePanel;

    QScrollArea *viewScroller;

    QVBoxLayout *layout;

signals:

};

#endif // HEIGHTMAPFRAME_H
