#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QPointF>
#include <QMouseEvent>
#include <QColor>


class DragWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = 0,QPointF* point = 0, QColor color = Q_NULLPTR );

    QPointF * point;



protected:

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:

    bool moving;

    bool posOk(QPoint point);


signals:



public slots:
};

#endif // DRAGWIDGET_H
