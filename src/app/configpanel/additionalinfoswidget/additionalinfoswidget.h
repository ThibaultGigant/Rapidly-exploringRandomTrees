#ifndef ADDITIONALINFOSWIDGET_H
#define ADDITIONALINFOSWIDGET_H

#include <QFrame>
#include <QVBoxLayout>
#include "nbrunsframe.h"
#include "sleeptimeframe.h"

class AdditionalInfosWidget : public QFrame
{
    Q_OBJECT
public:
    explicit AdditionalInfosWidget(QWidget *parent = 0);
    ~AdditionalInfosWidget();
    int getNbRuns();
    int getSleepTime();

private:
    QVBoxLayout *globalLayout;
    NbRunsFrame *nbRunsFrame;
    SleepTimeFrame *sleepTimeFrame;

signals:

public slots:
};

#endif // ADDITIONALINFOSWIDGET_H
