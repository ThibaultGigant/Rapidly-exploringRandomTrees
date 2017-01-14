#ifndef ADDITIONALINFOSWIDGET_H
#define ADDITIONALINFOSWIDGET_H

#include <QFrame>
#include <QVBoxLayout>
#include <QCheckBox>
#include "deltatframe.h"
#include "nbrunsframe.h"
#include "sleeptimeframe.h"

class AdditionalInfosWidget : public QFrame
{
    Q_OBJECT
public:
    explicit AdditionalInfosWidget(QWidget *parent = 0);
    ~AdditionalInfosWidget();
    double getDeltaT();
    int getNbRuns();
    int getSleepTime();
    Qt::CheckState getSaveState();

private:
    QVBoxLayout *globalLayout;
    DeltaTFrame *deltaTFrame;
    NbRunsFrame *nbRunsFrame;
    SleepTimeFrame *sleepTimeFrame;
    QCheckBox *saveCheckBox;

signals:

public slots:
};

#endif // ADDITIONALINFOSWIDGET_H
