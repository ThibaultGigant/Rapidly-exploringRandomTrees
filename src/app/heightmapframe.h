#ifndef HEIGHTMAPFRAME_H
#define HEIGHTMAPFRAME_H

#include <QWidget>
#include "heightmapsubpanel.h"
#include "heightmapsuppanel.h"
#include "heightmapviewpanel.h"

class HeightMapFrame : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFrame(QWidget *parent = 0);

private :

   HeighMapSubPanel hmSubPanel;
   HeighMapViewPanel hmViewPanel;
   HeighMapSupPanel hmSupPanel;

   QVBoxLayout layout;

signals:

public slots:

};

#endif // HEIGHTMAPFRAME_H
