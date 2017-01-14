#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QPointF>
#include <QMouseEvent>
#include <QColor>

#include "src/app/centralwidget.h"



class DragWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = 0,CentralWidget *cw = 0, QPointF* point = 0, QString = "" );




protected:

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:

    QPointF * point;
    CentralWidget *cw;

    bool moving;

    bool posOk(QPoint point);
    QPoint toScale(QPoint point);

signals:



public slots:
};

#endif // DRAGWIDGET_H
