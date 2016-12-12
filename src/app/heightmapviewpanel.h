#ifndef HEIGHTMAPVIEWPANEL_H
#define HEIGHTMAPVIEWPANEL_H

#include <QObject>
#include <QWidget>
#include "../classes/config.h"

class HeightMapViewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapViewPanel(QWidget *parent = 0, Config *config = 0);


private :
    Config *config;

signals:

public slots:
};

#endif // HEIGHTMAPVIEWPANEL_H
