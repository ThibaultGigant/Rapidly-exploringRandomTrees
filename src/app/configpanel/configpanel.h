#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "endmethodwidget.h"
#include "generatorwidget.h"
#include "metricwidget.h"
#include "additionalinfoswidget.h"

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

signals:

public slots:
};

#endif // CONFIGPANEL_H
