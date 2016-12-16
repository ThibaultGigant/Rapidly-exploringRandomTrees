#ifndef ENDMETHODPANEL_H
#define ENDMETHODPANEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QCheckBox>
#include "nbverticeslimitwidget.h"
#include "timelimitwidget.h"

class EndMethodWidget : public QFrame
{
    Q_OBJECT
public:
    explicit EndMethodWidget(QWidget *parent = 0);
    ~EndMethodWidget();

    qint64 getMaxNbVertices();
    time_t getTimeLimit();

private:
    QVBoxLayout *globalLayout;

    QLabel *title;
    NbVerticesLimitWidget *nbVerticesFrame;
    TimeLimitWidget *timeLimitFrame;

signals:

public slots:
};

#endif // ENDMETHODPANEL_H