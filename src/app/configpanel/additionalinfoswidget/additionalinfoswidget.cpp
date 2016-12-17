#include "additionalinfoswidget.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
AdditionalInfosWidget::AdditionalInfosWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->globalLayout = new QVBoxLayout(this);
    this->nbRunsFrame = new NbRunsFrame();
    this->sleepTimeFrame = new SleepTimeFrame();

    // Adding widgets to layouts
    this->globalLayout->addWidget(this->nbRunsFrame);
    this->globalLayout->addWidget(this->sleepTimeFrame);

    // Displaying the layout
    this->setLayout(this->globalLayout);
}

/**
 * @brief Destructor
 */
AdditionalInfosWidget::~AdditionalInfosWidget()
{
    delete this->globalLayout;
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
