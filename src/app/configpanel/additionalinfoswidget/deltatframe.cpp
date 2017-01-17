#include "deltatframe.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
DeltaTFrame::DeltaTFrame(ConfigPanel *cp, QWidget *parent) : QFrame(parent)
{
    this->cp = cp;

    // Layouts initialization
    this->layout = new QHBoxLayout(this);

    // Widgets initialization
    this->label = new QLabel("delta_t :");
    this->spinBox = new QDoubleSpinBox();

    // Setting up spinbox
    this->spinBox->setRange(1, 100);
    this->spinBox->setValue(20);

    // Adding widgets to layouts
    this->layout->addWidget(this->label);
    this->layout->addWidget(this->spinBox);

    // Displaying the layout
    this->setLayout(this->layout);

    // Connecting widgets to the configpanel
    connect(this->spinBox, SIGNAL(valueChanged(double)), cp, SLOT(configChanged()));
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

/**
 * @brief Sets the delta_t displayed in the spinbox
 * @param value Value of the delta_t to set
 */
void DeltaTFrame::setDeltaT(double value)
{
    this->spinBox->setValue(value);
}
