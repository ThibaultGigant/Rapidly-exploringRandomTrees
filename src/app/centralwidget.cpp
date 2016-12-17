#include "centralwidget.h"
#include "heightmappanel/heightmapframe.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    // Variables initialization
    this->configs = QVector<Config*>();
    this->currentMap = new HeightMap(NAME, WIDTH, HEIGHT, START_POINT, END_POINT);

    // Widgets initialization
    layout = new QHBoxLayout;
    hmFrame = new HeightMapFrame(this);
    this->configPanel = new ConfigPanel(this);

    // Adding widgets to layout
    layout->addWidget(hmFrame);
    layout->addWidget(this->configPanel);

    // Displaying layout
    setLayout(layout);

}

/**
 * @brief Destructor
 */
CentralWidget::~CentralWidget()
{
    delete currentMap;
    delete configPanel;
    delete hmFrame;
    delete layout;
}

/**
 * @brief Returns the current map to display
 * @return Current map
 */
HeightMap* CentralWidget::getCurrentMap()
{
    return this->currentMap;
}

/**
 * @brief Adds a config to the list of configs
 * @param config Config to add
 */
void CentralWidget::addConfig(Config *config)
{
    this->configs.append(config);
}

/**
 * @brief Starts the simulations for each configuration
 */
void CentralWidget::start()
{
    Session *session;
    Config *config;
    foreach (config, this->configs) {
        for (int i = 0; i < config->getNbRuns(); i++)
        {
            connect(config, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(receiveDrawElement(Vertex*)));
            connect(config, SIGNAL(emitUpdateImage()), this, SLOT(receiveUpdateImage()));
            session = new Session(config);
            config->getGenerator()->setSession(session);
            session->generate();
            disconnect(config, SIGNAL(emitDrawElement(Vertex*)), this, SLOT(receiveDrawElement(Vertex*)));
            disconnect(config, SIGNAL(emitUpdateImage()), this, SLOT(receiveUpdateImage()));
        }
    }
}

/**
 * @brief Receives the signal asking to draw a new element and forwards it
 * @param vertex Vertex to add to the display
 */
void CentralWidget::receiveDrawElement(Vertex *vertex)
{
    emit emitDrawElement(vertex);
}

/**
 * @brief Receives the signal asking to update the image and forwards it
 */
void CentralWidget::receiveUpdateImage()
{
    emit emitUpdateImage();
}
