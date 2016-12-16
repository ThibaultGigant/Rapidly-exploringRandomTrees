#ifndef GENERATORPANEL_H
#define GENERATORPANEL_H

#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>

class GeneratorWidget : public QFrame
{
    Q_OBJECT
public:
    explicit GeneratorWidget(QWidget *parent = 0);
    ~GeneratorWidget();
    int getGenerator();

private:
    QVBoxLayout *layout;
    QLabel *title;
    QComboBox *comboBox;

signals:

public slots:
};

#endif // GENERATORPANEL_H
