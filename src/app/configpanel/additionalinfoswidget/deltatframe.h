#ifndef DELTATFRAME_H
#define DELTATFRAME_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QString>

class DeltaTFrame : public QFrame
{
    Q_OBJECT
public:
    explicit DeltaTFrame(QWidget *parent = 0);
    ~DeltaTFrame();
    double getDeltaT();

private:
    QHBoxLayout *layout;
    QLabel *label;
    QDoubleSpinBox *spinBox;

signals:

public slots:
};

#endif // DELTATFRAME_H
