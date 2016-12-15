#include "configpanel.h"

ConfigPanel::ConfigPanel(QWidget *parent) : QWidget(parent)
{
    this->layout = new QVBoxLayout();

    // Initialization of the Widgets
    this->endMethodWidget = new EndMethodWidget(this);
    this->generatorWidget = new GeneratorWidget(this);
    this->metricWidget = new MetricWidget(this);
    this->additionalInfosWidget = new AdditionalInfosWidget(this);

    // Adding widgets to the layout
    this->layout->addWidget(this->endMethodWidget);
    this->layout->addWidget(this->generatorWidget);
    this->layout->addWidget(this->metricWidget);
    this->layout->addWidget(this->additionalInfosWidget);

    // displaying the layout
    this->setLayout(this->layout);
}
