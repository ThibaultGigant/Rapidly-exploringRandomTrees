#include "sleeptimeframe.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
SleepTimeFrame::SleepTimeFrame(QWidget *parent) : QWidget(parent)
{
    // Layouts initialization
    this->sleepTimeLayout = new QHBoxLayout(this);

    // Widgets initialization
    this->sleepTimeLabel = new QLabel("Sleep time :");
    this->sleepTimeSpinBox = new QSpinBox();

    // Setting up spinboxes
    this->sleepTimeSpinBox->setRange(0, 1000);
    this->sleepTimeSpinBox->setValue(10);
    this->sleepTimeSpinBox->setSuffix(" ms");

    // Adding widgets to layouts
    this->sleepTimeLayout->addWidget(this->sleepTimeLabel);
    this->sleepTimeLayout->addWidget(this->sleepTimeSpinBox);

    // Displaying the layout
    this->setLayout(this->sleepTimeLayout);
}

/**
 * @brief Destructor
 */
SleepTimeFrame::~SleepTimeFrame()
{
    delete this->sleepTimeLabel;
    delete this->sleepTimeSpinBox;
    delete this->sleepTimeLayout;
}

/**
 * @brief Returns how long the user wants to wait between the generation of 2 vertices
 * @return Sleep time between two generations
 */
int SleepTimeFrame::getSleepTime()
{
    return this->sleepTimeSpinBox->value();
}
