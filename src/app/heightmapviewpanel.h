#ifndef HEIGHTMAPVIEWPANEL_H
#define HEIGHTMAPVIEWPANEL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPointF>
#include <QColor>
#include <QPen>
#include <QScrollArea>
#include <QVector>
#include <QMouseEvent>
#include "../classes/config.h"
#include "../classes/environment/vertex.h"

class HeightMapViewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapViewPanel(QWidget *parent = 0, Config *config = 0);


private :
    Config *config;
    QImage view;

    QVector<Vertex*> vertexList;

    bool drawingAllowed;

    QPen hmPen;
    QPen edgePen;
    QBrush brush;

    bool scribbling;
    QPoint lastPoint;

    void setupPens();

    void drawLineTo(const QPoint &endPoint);


    void drawVertices(QPainter painter);
    void drawHeightMap();
    void drawImageOnHeightMap();

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

    void updateImage();
    void addElement(Vertex *vertex);
    void clear(bool doUpdateImage);
    void setDrawPermission(bool isDrawingAllowed);



};

#endif // HEIGHTMAPVIEWPANEL_H
