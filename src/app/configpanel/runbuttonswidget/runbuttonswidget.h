#ifndef RUNBUTTONSWIDGET_H
#define RUNBUTTONSWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

class CentralWidget;
class ConfigPanel;

class RunButtonsWidget : public QFrame
{
    Q_OBJECT
public:
    explicit RunButtonsWidget(QWidget *parent = 0);
    ~RunButtonsWidget();
    void isRun(bool b);
    void isModified(bool toUpdate);
    void isNotModified();

private:
    QHBoxLayout *layout;
    QPushButton *addButton;
    QPushButton *runButton;
    CentralWidget *cw;
    ConfigPanel *cp;

signals:
    void isRunning(bool b);

public slots:
    void toRun();
    void toStop();
};

#endif // RUNBUTTONSWIDGET_H
