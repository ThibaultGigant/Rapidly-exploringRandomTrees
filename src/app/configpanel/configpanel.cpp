#include "configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget, the central widget
 */
ConfigPanel::ConfigPanel(QWidget *parent) : QWidget(parent)
{
    this->changed = true;
    this->centralWidget = (CentralWidget *) parent;
    this->layout = new QVBoxLayout();

    // Initialization of the Widgets
    this->endMethodWidget = new EndMethodWidget(this);
    this->generatorWidget = new GeneratorWidget(this);
    this->metricWidget = new MetricWidget(this);
    this->additionalInfosWidget = new AdditionalInfosWidget(this);
    this->runButtonsWidget = new RunButtonsWidget(this);
    this->listWidget = new ListWidget(this);

    // Adding widgets to the layout
    this->layout->addWidget(this->endMethodWidget);
    this->layout->addWidget(this->generatorWidget);
    this->layout->addWidget(this->metricWidget);
    this->layout->addWidget(this->additionalInfosWidget);
    this->layout->addWidget(this->runButtonsWidget);
    this->layout->addWidget(this->listWidget);

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
 * @brief Getter of the flag stating if the config has been changed since it has been loaded
 * @return True if the config has been changed, false otherwise
 */
bool ConfigPanel::getChanged() const
{
    return changed;
}

/**
 * @brief Setter of the flag stating if the config has been changed since it's been loaded
 * @param value New value of the flag
 */
void ConfigPanel::setChanged(bool value)
{
    changed = value;
}

/**
 * @brief Receives a signal to add the current config to the list of configs
 * Creates a configuration according to the current configuration, then gives it to the central widget
 */
void ConfigPanel::addConfig()
{
    //qDebug() << "ConfigPanel addConfig : starting generation of config";
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
    //config->setGenerator(this->generatorWidget->getGenerator());
    //config->setMetric(this->metricWidget->getMetric());
    config->setGeneratorID(this->generatorWidget->getGeneratorID());
    config->setMetricID(this->metricWidget->getMetricID());
    config->setDelta_t(this->additionalInfosWidget->getDeltaT());
    config->setNbRuns(this->additionalInfosWidget->getNbRuns());
    config->setSleepTime(this->additionalInfosWidget->getSleepTime());

    this->centralWidget->addConfig(config);
    this->listWidget->addItem("config " + QString::number(this->centralWidget->getNbConfigs()));

    this->configUnChanged();
}

/**
 * @brief Receives the signal to start the simulation
 * Asks the central widget to launch the simulation
 */
void ConfigPanel::start()
{
    this->centralWidget->start();
}

/**
 * @brief Receives a signal that the config has changed
 */
void ConfigPanel::configChanged()
{
    this->setChanged(true);
    this->runButtonsWidget->isModified();
}

/**
 * @brief Receives a signal stating that the config hasn't changed since it's been loaded
 */
void ConfigPanel::configUnChanged()
{
    this->setChanged(false);
    this->runButtonsWidget->isNotModified();
}
