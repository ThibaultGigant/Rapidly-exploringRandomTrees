#ifndef HEIGHTMAPFRAME_H
#define HEIGHTMAPFRAME_H

#include <QWidget>
#include <QVBoxLayout>
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

    QVBoxLayout *layout;

signals:

};

#endif // HEIGHTMAPFRAME_H
