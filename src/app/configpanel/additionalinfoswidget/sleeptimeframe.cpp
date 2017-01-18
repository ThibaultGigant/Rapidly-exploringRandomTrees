#include "sleeptimeframe.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param cp ConfigPanel, used to centralize informations about the config
 * @param parent Widget's parent
 */
SleepTimeFrame::SleepTimeFrame(ConfigPanel *cp, QWidget *parent) : QWidget(parent)
{
    this->cp = cp;
    // Layouts initialization
    this->sleepTimeLayout = new QHBoxLayout(this);

    // Widgets initialization
    this->sleepTimeLabel = new QLabel("Sleep time :");
    this->sleepTimeSpinBox = new QSpinBox();

    // Setting up spinboxes
    this->sleepTimeSpinBox->setRange(0, 10000);
    this->sleepTimeSpinBox->setValue(1);
    this->sleepTimeSpinBox->setSuffix(" ms");

    // Adding widgets to layouts
    this->sleepTimeLayout->addWidget(this->sleepTimeLabel);
    this->sleepTimeLayout->addWidget(this->sleepTimeSpinBox);

    // Displaying the layout
    this->setLayout(this->sleepTimeLayout);

    // Connecting the widgets to the configpanel
    connect(this->sleepTimeSpinBox, SIGNAL(valueChanged(int)), cp, SLOT(configChanged()));
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

/**
 * @brief Sets the sleeptime in the displayed spinbox
 * @param value Value to display
 */
void SleepTimeFrame::setSleepTime(int value)
{
    this->sleepTimeSpinBox->setValue(value);
}
