#ifndef TIMELIMITWIDGET_H
#define TIMELIMITWIDGET_H

#include <QFrame>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <ctime>

class TimeLimitWidget : public QFrame
{
    Q_OBJECT
public:
    explicit TimeLimitWidget(QWidget *parent = 0);
    ~TimeLimitWidget();

    time_t getTimeLimit();

private:
    QHBoxLayout *layout;
    QCheckBox *checkBox;
    QSpinBox *spinBox;

signals:

public slots:
    void manageSpinbox(int toDisplay);
};

#endif // TIMELIMITWIDGET_H
