#include "metricwidget.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
MetricWidget::MetricWidget(QWidget *parent) : QFrame(parent)
{
    ConfigPanel *cp = (ConfigPanel *) parent;

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

    connect(this->comboBox, SIGNAL(currentIndexChanged(int)), cp, SLOT(configChanged()));
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

/**
 * @brief Sets the current metric in the combobox
 * @param value Index of the metric to set
 */
void MetricWidget::setMetricID(int value)
{
    this->comboBox->setCurrentIndex(value);
}
