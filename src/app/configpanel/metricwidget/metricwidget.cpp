#include "metricwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
MetricWidget::MetricWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QVBoxLayout(this);
    this->title = new QLabel("Choose a metric :");
    this->comboBox = new QComboBox();

    // Adding items to the combobox
    this->comboBox->addItem("Euclidian distance");
    this->comboBox->addItem("Manhattan distance");

    this->comboBox->setCurrentIndex(0); // Set combobox to a default value

    // Adding widgets to layout
    this->layout->addWidget(this->title);
    this->layout->addWidget(this->comboBox);
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
