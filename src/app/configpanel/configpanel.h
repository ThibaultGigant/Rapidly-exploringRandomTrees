#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include "endmethodwidget/endmethodwidget.h"
#include "generatorwidget/generatorwidget.h"
#include "metricwidget/metricwidget.h"
#include "additionalinfoswidget/additionalinfoswidget.h"
#include "runbuttonswidget/runbuttonswidget.h"
#include "listwidget/listwidget.h"

class CentralWidget;

class ConfigPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPanel(QWidget *parent = 0);
    ~ConfigPanel();

    CentralWidget *getCentralWidget() const;

    bool getChanged() const;
    void setChanged(bool value);

private:
    CentralWidget *centralWidget;
    QVBoxLayout *layout;

    EndMethodWidget *endMethodWidget;
    GeneratorWidget *generatorWidget;
    MetricWidget *metricWidget;
    AdditionalInfosWidget *additionalInfosWidget;
    RunButtonsWidget *runButtonsWidget;
    ListWidget *listWidget;

    bool changed;
    int currentConfigID;

signals:

public slots:
    void addConfig();
    void start();
    void configChanged();
    void configUnChanged();
    void loadConfig(int configIndex);
};

#endif // CONFIGPANEL_H
