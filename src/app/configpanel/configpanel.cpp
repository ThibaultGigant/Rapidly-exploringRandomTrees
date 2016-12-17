#include "configpanel.h"

ConfigPanel::ConfigPanel(QWidget *parent) : QWidget(parent)
{
    this->layout = new QVBoxLayout();

    // Initialization of the Widgets
    this->endMethodWidget = new EndMethodWidget();
    this->generatorWidget = new GeneratorWidget();
    this->metricWidget = new MetricWidget();
    this->additionalInfosWidget = new AdditionalInfosWidget();
    this->runButtonsWidget = new RunButtonsWidget();

    // Adding widgets to the layout
    this->layout->addWidget(this->endMethodWidget);
    this->layout->addWidget(this->generatorWidget);
    this->layout->addWidget(this->metricWidget);
    this->layout->addWidget(this->additionalInfosWidget);
    this->layout->addWidget(this->runButtonsWidget);

    // displaying the layout
    this->setLayout(this->layout);
}
