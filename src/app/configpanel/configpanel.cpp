#include "configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget, the central widget
 */
ConfigPanel::ConfigPanel(QWidget *parent) : QWidget(parent)
{
    this->centralWidget = (CentralWidget *) parent;
    this->layout = new QVBoxLayout();

    // Initialization of the Widgets
    this->endMethodWidget = new EndMethodWidget(this);
    this->generatorWidget = new GeneratorWidget(this);
    this->metricWidget = new MetricWidget(this);
    this->additionalInfosWidget = new AdditionalInfosWidget(this);
    this->runButtonsWidget = new RunButtonsWidget(this);

    // Adding widgets to the layout
    this->layout->addWidget(this->endMethodWidget);
    this->layout->addWidget(this->generatorWidget);
    this->layout->addWidget(this->metricWidget);
    this->layout->addWidget(this->additionalInfosWidget);
    this->layout->addWidget(this->runButtonsWidget);

    // displaying the layout
    this->setLayout(this->layout);
}

/**
 * @brief Destructor
 */
ConfigPanel::~ConfigPanel()
{
    delete this->endMethodWidget;
    delete this->generatorWidget;
    delete this->metricWidget;
    delete this->additionalInfosWidget;
    delete this->runButtonsWidget;
    delete this->layout;
}

/**
 * @brief Returns the central Widget
 * @return Central Widget
 */
CentralWidget *ConfigPanel::getCentralWidget() const
{
    return centralWidget;
}

/**
 * @brief Receives a signal to add the current config to the list of configs
 * Creates a configuration according to the current configuration, then gives it to the central widget
 */
void ConfigPanel::addConfig()
{
    EndMethod *endMethod = this->endMethodWidget->getEndMethod();
    if (endMethod->getMaxNumber() <= 1 && endMethod->getLimitTime() == 0)
    {
        QMessageBox msgBox(QMessageBox::Critical, "Error: Wrong End Method",
                           "Please select a correct End Method", QMessageBox::Close);
        msgBox.exec();
        return;
    }

    // Creating the config to pass on
    Config *config = new Config();
    config->setCurrentMap(this->centralWidget->getCurrentMap());
    config->setEndMethod(this->endMethodWidget->getEndMethod());
    config->setGenerator(this->generatorWidget->getGenerator());
    config->setMetric(this->metricWidget->getMetric());
    config->setDelta_t(this->additionalInfosWidget->getDeltaT());
    config->setNbRuns(this->additionalInfosWidget->getNbRuns());
    config->setSleepTime(this->additionalInfosWidget->getSleepTime());

    this->centralWidget->addConfig(config);
}

/**
 * @brief Receives the signal to start the simulation
 * Asks the central widget to launch the simulation
 */
void ConfigPanel::start()
{
    this->centralWidget->start();
}
