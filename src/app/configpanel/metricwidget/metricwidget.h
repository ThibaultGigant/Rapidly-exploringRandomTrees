#ifndef METRICPANEL_H
#define METRICPANEL_H

#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include "src/classes/metrics/euclidiandistance.h"
#include "src/classes/metrics/manhattandistance.h"

class MetricWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MetricWidget(QWidget *parent = 0);
    ~MetricWidget();
    Metric* getMetric();
    int getMetricID();

private:
    QHBoxLayout *layout;
    QLabel *title;
    QComboBox *comboBox;

signals:

public slots:
};

#endif // METRICPANEL_H
