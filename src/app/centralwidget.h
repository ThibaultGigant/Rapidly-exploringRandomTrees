#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "src/app/heightmappanel/heightmapframe.h"
#include "src/classes/config.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0, Config *config = 0);

private :

    Config *config;
    QHBoxLayout *layout;
    HeightMapFrame *hmFrame;

signals:



public slots:
};

#endif // CENTRALWIDGET_H
