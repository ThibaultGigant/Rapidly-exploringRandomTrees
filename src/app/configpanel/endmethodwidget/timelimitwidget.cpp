#include "timelimitwidget.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param cp ConfigPanel, used to centralize informations about the config
 * @param parent Parent of the Widget
 */
TimeLimitWidget::TimeLimitWidget(ConfigPanel *cp, QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->checkBox = new QCheckBox("Time limit");
    this->spinBox = new QSpinBox();

    // Setting spinbox values
    this->spinBox->setRange(1, 3600);
    this->spinBox->setValue(10);
    this->spinBox->setSuffix(" s");

    // Adding widget
    this->layout->addWidget(this->checkBox);

    // Adding the connection between the checkbox and the display of the spinbox
    connect(this->checkBox, SIGNAL(stateChanged(int)), this, SLOT(manageSpinbox(int)));
    connect(this->checkBox, SIGNAL(stateChanged(int)), cp, SLOT(configChanged()));
    connect(this->spinBox, SIGNAL(valueChanged(int)), cp, SLOT(configChanged()));
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
    {
        this->layout->addWidget(this->spinBox);
        this->spinBox->show();
    }
    else
    {
        this->layout->removeWidget(this->spinBox);
        this->spinBox->hide();
    }
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

/**
 * @brief Sets the time limit and displays it in the spinbox
 * @param value New value of the time limit
 */
void TimeLimitWidget::setTimeLimit(time_t value)
{
    if (value > 0)
    {
        this->checkBox->setChecked(Qt::Checked);
        this->spinBox->setValue((int) value);
    }
    else
        this->checkBox->setChecked(Qt::Unchecked);
}
