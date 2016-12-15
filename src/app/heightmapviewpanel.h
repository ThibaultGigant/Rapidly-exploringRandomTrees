#ifndef HEIGHTMAPVIEWPANEL_H
#define HEIGHTMAPVIEWPANEL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPointF>
#include <QColor>
#include <QScrollArea>
#include <QMouseEvent>
#include "../classes/config.h"

class HeightMapViewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapViewPanel(QWidget *parent = 0, Config *config = 0);


private :
    Config *config;
    QImage view;

    QBrush edgeBrush;
    QBrush vertexBrush;

    int vertexCount;
    bool scribbling;
    QPoint lastPoint;

    void updateViewImage();
    void drawLineTo(const QPoint &endPoint);

    QPoint toScreenPix(QPointF p);
    QPoint toScreenPix(QPoint p);
    QPointF toHeightMapPoint(QPoint p);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
    void drawElement(Vertex *vertex);


};

#endif // HEIGHTMAPVIEWPANEL_H
