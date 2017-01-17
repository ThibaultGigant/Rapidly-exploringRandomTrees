#ifndef NBVERTICESLIMITWIDGET_H
#define NBVERTICESLIMITWIDGET_H

#include <QFrame>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>

class ConfigPanel;

class NbVerticesLimitWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NbVerticesLimitWidget(ConfigPanel *cp, QWidget *parent = 0);
    ~NbVerticesLimitWidget();

    qint64 getMaxNbVertices();
    void setMaxNbVertices(qint64 value);

private:
    QHBoxLayout *layout;
    QCheckBox *checkBox;
    QSpinBox *spinBox;

signals:

public slots:
    void manageSpinbox(int toDisplay);
};

#endif // NBVERTICESLIMITWIDGET_H
