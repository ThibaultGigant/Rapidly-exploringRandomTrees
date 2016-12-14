#ifndef HEIGHTMAPVIEWPANEL_H
#define HEIGHTMAPVIEWPANEL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QColor>
#include "../classes/config.h"

class HeightMapViewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapViewPanel(QWidget *parent = 0, Config *config = 0);


private :
    Config *config;
    QImage view;

    QPoint toScreenPix(QPointF p);
    QPoint toScreenPix(QPoint p);
    QPointF toHeightMapPoint(QPoint p);

protected:
    void paintEvent(QPaintEvent* event);

signals:

public slots:
    void drawElement(Vertex *vertex);


};

#endif // HEIGHTMAPVIEWPANEL_H
