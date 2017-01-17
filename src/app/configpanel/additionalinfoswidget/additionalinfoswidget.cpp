#include "additionalinfoswidget.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
AdditionalInfosWidget::AdditionalInfosWidget(QWidget *parent) : QFrame(parent)
{
    ConfigPanel *p = (ConfigPanel*) parent;
    // Widgets initialization
    this->globalLayout = new QVBoxLayout(this);
    this->deltaTFrame = new DeltaTFrame(p);
    this->nbRunsFrame = new NbRunsFrame(p);
    this->sleepTimeFrame = new SleepTimeFrame(p);
    this->saveCheckBox = new QCheckBox("Save results ?");

    // Adding widgets to layouts
    this->globalLayout->addWidget(this->deltaTFrame);
    this->globalLayout->addWidget(this->nbRunsFrame);
    this->globalLayout->addWidget(this->sleepTimeFrame);
    this->globalLayout->addWidget(this->saveCheckBox);

    // Displaying the layout
    this->setLayout(this->globalLayout);

    // Connecting the widgets to the configpanel
    // connect(this->saveCheckBox, SIGNAL(stateChanged(int)), p, SLOT(configChanged()));
}

/**
 * @brief Destructor
 */
AdditionalInfosWidget::~AdditionalInfosWidget()
{
    delete this->deltaTFrame;
    delete this->nbRunsFrame;
    delete this->sleepTimeFrame;
    delete this->globalLayout;
    delete this->saveCheckBox;
}

/**
 * @brief Returns the delta_t chosen by the user
 * @return delta_t chosen
 */
double AdditionalInfosWidget::getDeltaT()
{
    return this->deltaTFrame->getDeltaT();
}

/**
 * @brief Returns how many simulations the user wants to run
 * @return Number of runs to launch
 */
int AdditionalInfosWidget::getNbRuns()
{
    return this->nbRunsFrame->getNbRuns();
}

/**
 * @brief Returns how long the user wants to wait between the generation of 2 vertices
 * @return Sleep time between two generations
 */
int AdditionalInfosWidget::getSleepTime()
{
    return this->sleepTimeFrame->getSleepTime();
}

/**
 * @brief Returns whether the "save" checkbox is checked or not
 * @return CheckState of the save checkbox
 */
Qt::CheckState AdditionalInfosWidget::getSaveState()
{
    return this->saveCheckBox->checkState();
}
