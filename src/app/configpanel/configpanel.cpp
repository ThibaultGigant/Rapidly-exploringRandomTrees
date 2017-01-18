#include "configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget, the central widget
 */
ConfigPanel::ConfigPanel(QWidget *parent) : QWidget(parent)
{
    this->changed = true;
    this->isConfigFromList = false;
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
    Config *config;

    //qDebug() << "ConfigPanel addConfig : adding config #" << this->currentConfigID;
    // Creating the config to pass on
    if (!this->isConfigFromList)
        config = new Config();
    else
        config = this->getCentralWidget()->getConfigs().at(this->currentConfigID);

    //qDebug() << "ConfigPanel addConfig : starting generation of config";
    if (config->getNbVerticesLimit() <= 1 && config->getTimeDuration() == 0)
    {
        QMessageBox msgBox(QMessageBox::Critical, "Error: Wrong End Method",
                           "Please select a correct End Method", QMessageBox::Close);
        msgBox.exec();
        return;
    }

    this->centralWidget->receiveClearImage(0);
    config->setCurrentMap(this->centralWidget->getCurrentMap());
    config->setEndMethod(this->endMethodWidget->getEndMethod());
    config->setGeneratorID(this->generatorWidget->getGeneratorID());
    config->setMetricID(this->metricWidget->getMetricID());
    config->setDelta_t(this->additionalInfosWidget->getDeltaT());
    config->setNbRuns(this->additionalInfosWidget->getNbRuns());
    config->setSleepTime(this->additionalInfosWidget->getSleepTime());

    if (!this->isConfigFromList)
    {
        this->centralWidget->addConfig(config);
        this->listWidget->addItem("config " + QString::number(this->centralWidget->getNbConfigs()));
    }

    this->configUnChanged();
    this->isConfigFromList = false;
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
    this->runButtonsWidget->isModified(this->isConfigFromList);
}

/**
 * @brief Receives a signal stating that the config hasn't changed since it's been loaded
 */
void ConfigPanel::configUnChanged()
{
    this->setChanged(false);
    this->runButtonsWidget->isNotModified();
}

/**
 * @brief Loads the config and displays it
 * @param configIndex Index of the config to load
 */
void ConfigPanel::loadConfig(int configIndex)
{
    //qDebug() << "ConfigPanel LoadConfig : loading config #" << configIndex;
    if (configIndex >= 0)
    {
        // Storing the current config if it has changed
        if (this->changed)
            this->addConfig();
        this->isConfigFromList = true;

        // Loading of the config
        this->currentConfigID = configIndex;

        Config *config = this->centralWidget->getConfigs().at(configIndex);

        this->endMethodWidget->setMaxNbVertices(config->getNbVerticesLimit());
        this->endMethodWidget->setTimeLimit(config->getTimeDuration());
        this->generatorWidget->setGeneratorID(config->getGeneratorID());
        this->metricWidget->setMetricID(config->getMetricID());
        this->additionalInfosWidget->setDeltaT(config->getDelta_t());
        this->additionalInfosWidget->setNbRuns(config->getNbRuns());
        this->additionalInfosWidget->setSleepTime(config->getNbRuns());
        this->centralWidget->setCurrentMap(config->getCurrentMap());
        this->centralWidget->receiveClearImage(0);
        this->configUnChanged();
    }
}

/**
 * @brief Returns whether the save checkbox has been checked
 * @return True if checked, false otherwise
 */
bool ConfigPanel::getSave()
{
    if (this->additionalInfosWidget->getSaveState() == Qt::Checked)
        return true;
    return false;
}

/**
 * @brief Returns if the config currently displayed is loaded from the stored list or not
 * @return True if the displayed config is loaded from the list
 */
bool ConfigPanel::getIsConfigFromList() const
{
    return isConfigFromList;
}

/**
 * @brief Sets the value of the boolean stating if the config loaded from the list
 * @param value New value of this boolean
 */
void ConfigPanel::setIsConfigFromList(bool value)
{
    isConfigFromList = value;
}
