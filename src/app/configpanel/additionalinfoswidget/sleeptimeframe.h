#ifndef SLEEPTIMEFRAME_H
#define SLEEPTIMEFRAME_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

class ConfigPanel;

class SleepTimeFrame : public QWidget
{
    Q_OBJECT
public:
    explicit SleepTimeFrame(ConfigPanel *cp, QWidget *parent = 0);
    ~SleepTimeFrame();
    int getSleepTime();
    void setSleepTime(int value);

private:
    QHBoxLayout *sleepTimeLayout;
    QLabel *sleepTimeLabel;
    QSpinBox *sleepTimeSpinBox;
    ConfigPanel *cp;
signals:

public slots:
};

#endif // SLEEPTIMEFRAME_H
