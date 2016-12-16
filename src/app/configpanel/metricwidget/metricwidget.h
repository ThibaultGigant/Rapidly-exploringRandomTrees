#ifndef METRICPANEL_H
#define METRICPANEL_H

#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>

class MetricWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MetricWidget(QWidget *parent = 0);
    ~MetricWidget();
    int getMetric();

private:
    QVBoxLayout *layout;
    QLabel *title;
    QComboBox *comboBox;

signals:

public slots:
};

#endif // METRICPANEL_H
