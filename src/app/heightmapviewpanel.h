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

    QPoint toScreenPix(QPointF p);
    QPointF toHeightMapPoint(QPoint p);

signals:

public slots:

    void drawLine(QPointF p1, QPointF p2);


};

#endif // HEIGHTMAPVIEWPANEL_H
