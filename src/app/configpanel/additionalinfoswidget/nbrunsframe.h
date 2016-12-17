#ifndef NBRUNSFRAME_H
#define NBRUNSFRAME_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

class NbRunsFrame : public QFrame
{
    Q_OBJECT
public:
    explicit NbRunsFrame(QWidget *parent = 0);
    ~NbRunsFrame();
    int getNbRuns();

private:
    QHBoxLayout *nbRunsLayout;
    QLabel *nbRunsLabel;
    QSpinBox *nbRunsSpinBox;

signals:

public slots:
};

#endif // NBRUNSFRAME_H
