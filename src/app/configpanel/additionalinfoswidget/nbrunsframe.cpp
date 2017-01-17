#include "nbrunsframe.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param parent Widget's Parent
 */
NbRunsFrame::NbRunsFrame(ConfigPanel *cp, QWidget *parent) : QFrame(parent)
{
    this->cp = cp;

    // Layouts initialization
    this->nbRunsLayout = new QHBoxLayout(this);

    // Widgets initialization
    this->nbRunsLabel = new QLabel("Number of simulations :");
    this->nbRunsSpinBox = new QSpinBox();

    // Setting up spinboxes
    this->nbRunsSpinBox->setRange(1, 100);
    this->nbRunsSpinBox->setValue(1);

    // Adding widgets to layouts
    this->nbRunsLayout->addWidget(this->nbRunsLabel);
    this->nbRunsLayout->addWidget(this->nbRunsSpinBox);

    // Displaying the layout
    this->setLayout(this->nbRunsLayout);

    // Connecting the widgets to the configpanel
    connect(this->nbRunsSpinBox, SIGNAL(valueChanged(int)), cp, SLOT(configChanged()));
}

/**
 * @brief Destructor
 */
NbRunsFrame::~NbRunsFrame()
{
    delete this->nbRunsLabel;
    delete this->nbRunsSpinBox;
    delete this->nbRunsLayout;
}

/**
 * @brief Returns how many simulations the user wants to run
 * @return Number of runs to launch
 */
int NbRunsFrame::getNbRuns()
{
    return this->nbRunsSpinBox->value();
}

/**
 * @brief Sets the number of simulations to launch in the displayed spinbox
 * @param value Value to display
 */
void NbRunsFrame::setNbRuns(int value)
{
    this->nbRunsSpinBox->setValue(value);
}
