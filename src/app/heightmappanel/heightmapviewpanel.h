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
#include "src/classes/environment/vertex.h"

class CentralWidget;

class HeightMapViewPanel : public QWidget
{
    Q_OBJECT
public:

    int MAX_SIZE = 30;
    int MIN_SIZE = 2;

    explicit HeightMapViewPanel(CentralWidget *centralWidget, QWidget *parent = 0);
    void drawImageOnHeightMap();
    int getPenSize();


private :

    CentralWidget *centralWidget;
    QImage view;
    unsigned char *data;
    int w,h;

    QVector<Vertex*> vertexList;

    bool modifAllowed;

    QPen hmPen;
    QPen edgePen;
    QBrush brush;

    bool scribbling;
    QPoint lastPoint;

    int count;
    int penSize;


    void setupPens();
    void setupImage();

    void drawLineTo(const QPoint &endPoint);


    void drawHeightMap();

    QPoint toScreenPix(QPointF p);
    QPoint toScreenPix(QPoint p);
    QPointF toHeightMapPoint(QPoint p);

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:

    void sendPenSize(int);
    void sendModifAllowed(bool);
    void lastVertexDrawn(Vertex *);

public slots:

    void addElement(Vertex *vertex);
    void clear(int count);
    void setModifPermission(bool isModifAllowed);

    void increasePenSize();
    void decreasePenSize();

};

#endif // HEIGHTMAPVIEWPANEL_H
