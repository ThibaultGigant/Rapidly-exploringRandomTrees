#ifndef HEIGHTMAPSUBPANEL_H
#define HEIGHTMAPSUBPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class HeightMapSubPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapSubPanel(QWidget *parent = 0);

private:

    QPushButton *penMode;
    QPushButton *circleMode;
    QPushButton *squareMode;

    QPushButton *clearMap;

    QPushButton *plusButton;
    QLabel *penSize;
    QPushButton *minusButton;


signals:

public slots:

};

#endif // HEIGHTMAPSUBPANEL_H
