#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "endmethodwidget/endmethodwidget.h"
#include "generatorwidget/generatorwidget.h"
#include "metricwidget/metricwidget.h"
#include "additionalinfoswidget/additionalinfoswidget.h"
#include "runbuttonswidget/runbuttonswidget.h"

class ConfigPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPanel(QWidget *parent = 0);

private:
    QVBoxLayout *layout;

    QWidget *endMethodWidget;
    QWidget *generatorWidget;
    QWidget *metricWidget;
    QWidget *additionalInfosWidget;
    QWidget *runButtonsWidget;

signals:

public slots:
};

#endif // CONFIGPANEL_H
