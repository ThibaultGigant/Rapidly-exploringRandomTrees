#ifndef RUNBUTTONSWIDGET_H
#define RUNBUTTONSWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

class RunButtonsWidget : public QFrame
{
    Q_OBJECT
public:
    explicit RunButtonsWidget(QWidget *parent = 0);
    ~RunButtonsWidget();

private:
    QHBoxLayout *layout;
    QPushButton *addButton;
    QPushButton *runButton;

signals:

public slots:
};

#endif // RUNBUTTONSWIDGET_H
