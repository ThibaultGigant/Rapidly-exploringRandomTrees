#ifndef HEIGHTMAPFRAME_H
#define HEIGHTMAPFRAME_H

#include <QWidget>
#include <QVBoxLayout>
#include "heightmapsubpanel.h"
#include "heightmapviewpanel.h"
#include "heightmapfilepanel.h"
#include "../classes/config.h"

class HeightMapFrame : public QWidget
{
    Q_OBJECT
public:
    explicit HeightMapFrame(QWidget *parent = 0, Config *config = 0);

private :

<<<<<<< Updated upstream
   HeightMapSubPanel hmSubPanel;
   HeightMapViewPanel hmViewPanel;
   HeightMapSupPanel hmSupPanel;
=======
    Config *config;
>>>>>>> Stashed changes

    HeightMapSubPanel *hmSubPanel;
    HeightMapViewPanel *hmViewPanel;
    HeightMapFilePanel *hmFilePanel;

    QVBoxLayout *layout;

signals:

public slots:

};

#endif // HEIGHTMAPFRAME_H
