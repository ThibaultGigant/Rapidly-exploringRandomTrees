#include "timelimitwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the Widget
 */
TimeLimitWidget::TimeLimitWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->checkBox = new QCheckBox("Time limit");
    this->spinBox = new QSpinBox();

    // Setting spinbox values
    this->spinBox->setRange(1, 3600);
    this->spinBox->setValue(0);
    this->spinBox->setSuffix("seconds");

    // Adding widget
    this->layout->addWidget(this->checkBox);

    // Adding the connection between the checkbox and the display of the spinbox
    connect(this->checkBox, SIGNAL(stateChanged(int)), this, SLOT(manageSpinbox(int)));
}

/**
 * @brief Destructor
 */
TimeLimitWidget::~TimeLimitWidget()
{
    delete checkBox;
    delete spinBox;
    delete layout;
}

/**
 * @brief Triggers the display of the spinbox allowing to choose the time limit
 * @param toDisplay Representing if the SpinBox should be displayed or not
 */
void TimeLimitWidget::manageSpinbox(int toDisplay)
{
    if (toDisplay)
        this->layout->addWidget(this->spinBox);
    else
        this->layout->removeWidget(this->spinBox);
}

/**
 * @brief Returns the choice of the user about the time limit
 * @return time limit
 */
time_t TimeLimitWidget::getTimeLimit()
{
    if (this->checkBox->checkState() == Qt::Unchecked)
        return (time_t) 0;
    return (time_t) this->spinBox->value();
}
