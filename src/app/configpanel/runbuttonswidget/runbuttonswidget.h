#ifndef RUNBUTTONSWIDGET_H
#define RUNBUTTONSWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

class CentralWidget;

class RunButtonsWidget : public QFrame
{
    Q_OBJECT
public:
    explicit RunButtonsWidget(QWidget *parent = 0);
    ~RunButtonsWidget();
    void isRun(bool b);

private:
    QHBoxLayout *layout;
    QPushButton *addButton;
    QPushButton *runButton;
    CentralWidget *cw;

signals:
    void isRunning(bool b);

public slots:
    void toRun();
    void toStop();
};

#endif // RUNBUTTONSWIDGET_H
