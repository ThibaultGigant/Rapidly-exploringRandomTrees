#ifndef GENERATORPANEL_H
#define GENERATORPANEL_H

#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include "src/classes/generators/randomtreegenerator.h"
#include "src/classes/generators/rrtgenerator.h"
#include "src/classes/generators/prmgenerator.h"

class GeneratorWidget : public QFrame
{
    Q_OBJECT
public:
    explicit GeneratorWidget(QWidget *parent = 0);
    ~GeneratorWidget();
    TreeGenerator* getGenerator();
    int getGeneratorID();
    void setGeneratorID(int value);

private:
    QHBoxLayout *layout;
    QLabel *title;
    QComboBox *comboBox;

signals:

public slots:
};

#endif // GENERATORPANEL_H
