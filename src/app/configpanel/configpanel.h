#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "endmethodwidget/endmethodwidget.h"
#include "generatorwidget/generatorwidget.h"
#include "metricwidget/metricwidget.h"
#include "additionalinfoswidget/additionalinfoswidget.h"
#include "runbuttonswidget/runbuttonswidget.h"

class CentralWidget;

class ConfigPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPanel(QWidget *parent = 0);
    ~ConfigPanel();

    CentralWidget *getCentralWidget() const;

private:
    CentralWidget *centralWidget;
    QVBoxLayout *layout;

    EndMethodWidget *endMethodWidget;
    GeneratorWidget *generatorWidget;
    MetricWidget *metricWidget;
    AdditionalInfosWidget *additionalInfosWidget;
    RunButtonsWidget *runButtonsWidget;

signals:

public slots:
    void addConfig();
    void start();
};

#endif // CONFIGPANEL_H
