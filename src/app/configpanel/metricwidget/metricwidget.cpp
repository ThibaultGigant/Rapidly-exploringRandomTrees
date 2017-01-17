#include "metricwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
MetricWidget::MetricWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->title = new QLabel("Choose a metric :");
    this->comboBox = new QComboBox();

    // Adding items to the combobox
    this->comboBox->addItem("Euclidian distance");
    this->comboBox->addItem("Manhattan distance");

    // Set combobox to a default value
    this->comboBox->setCurrentIndex(0);

    // Adding widgets to layout
    this->layout->addWidget(this->title);
    this->layout->addWidget(this->comboBox);

    // Displaying the layout
    this->setLayout(this->layout);
}

/**
 * @brief Destructor
 */
MetricWidget::~MetricWidget()
{
    delete this->title;
    delete this->comboBox;
    delete this->layout;
}

/**
 * @brief Returns the metric to use to calculate the distances during the simulation
 * @return Metric to use
 */
Metric* MetricWidget::getMetric()
{
    switch (this->comboBox->currentIndex()) {
    case 0:
        return new EuclidianDistance();
    case 1:
        return new ManhattanDistance();
    default:
        return new EuclidianDistance();
    }
}

/**
 * @brief Returns the ID of the metric to use
 * @return ID of the metric
 */
int MetricWidget::getMetricID()
{
    return this->comboBox->currentIndex();
}
