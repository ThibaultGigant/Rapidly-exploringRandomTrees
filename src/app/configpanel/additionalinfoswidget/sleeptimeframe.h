#ifndef SLEEPTIMEFRAME_H
#define SLEEPTIMEFRAME_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

class SleepTimeFrame : public QWidget
{
    Q_OBJECT
public:
    explicit SleepTimeFrame(QWidget *parent = 0);
    ~SleepTimeFrame();
    int getSleepTime();

private:
    QHBoxLayout *sleepTimeLayout;
    QLabel *sleepTimeLabel;
    QSpinBox *sleepTimeSpinBox;
signals:

public slots:
};

#endif // SLEEPTIMEFRAME_H
