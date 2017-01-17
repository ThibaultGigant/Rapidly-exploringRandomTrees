#ifndef NBRUNSFRAME_H
#define NBRUNSFRAME_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

class ConfigPanel;

class NbRunsFrame : public QFrame
{
    Q_OBJECT
public:
    explicit NbRunsFrame(ConfigPanel *cp,QWidget *parent = 0);
    ~NbRunsFrame();
    int getNbRuns();

private:
    QHBoxLayout *nbRunsLayout;
    QLabel *nbRunsLabel;
    QSpinBox *nbRunsSpinBox;
    ConfigPanel *cp;

signals:

public slots:
};

#endif // NBRUNSFRAME_H
