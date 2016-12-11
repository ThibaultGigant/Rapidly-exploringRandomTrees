#ifndef HEIGHTMAPFRAME_H
#define HEIGHTMAPFRAME_H

#include <QWidget>
#include <QVBoxLayout>
#include "heightmapsubpanel.h"
#include "heightmapsuppanel.h"
#include "heightmapviewpanel.h"

class HeightMapFrame : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFrame(QWidget *parent = 0);

private :

   HeightMapSubPanel hmSubPanel;
   HeightMapViewPanel hmViewPanel;
   HeightMapSupPanel hmSupPanel;

   QVBoxLayout layout;

signals:

public slots:

};

#endif // HEIGHTMAPFRAME_H
