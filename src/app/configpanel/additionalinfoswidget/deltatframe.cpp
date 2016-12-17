#include "deltatframe.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
DeltaTFrame::DeltaTFrame(QWidget *parent) : QFrame(parent)
{
    // Layouts initialization
    this->layout = new QHBoxLayout(this);

    // Widgets initialization
    this->label = new QLabel(QString::fromUtf8("CEB4") + " :");
    this->spinBox = new QDoubleSpinBox();

    // Setting up spinbox
    this->spinBox->setRange(1, 100);
    this->spinBox->setValue(10);

    // Adding widgets to layouts
    this->layout->addWidget(this->label);
    this->layout->addWidget(this->spinBox);

    // Displaying the layout
    this->setLayout(this->layout);
}

/**
 * @brief Destructor
 */
DeltaTFrame::~DeltaTFrame()
{
    delete this->label;
    delete this->spinBox;
    delete this->layout;
}

/**
 * @brief Returns the delta_t chosen by the user
 * @return delta_t chosen
 */
double DeltaTFrame::getDeltaT()
{
    return this->spinBox->value();
}
