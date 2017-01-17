#include "centralwidget.h"
#include "heightmappanel/heightmapframe.h"
#include "src/classes/threadgenerator.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    // Variables initialization
    this->configs = QVector<Config*>();
    this->currentMap = new HeightMap(NAME, WIDTH, HEIGHT, START_POINT, END_POINT);
    this->nbConfigs = 0;

    // Widgets initialization
    layout = new QHBoxLayout;
    hmFrame = new HeightMapFrame(this);
    this->configPanel = new ConfigPanel(this);

    //this->configPanel->setMaximumWidth(300);
    this->hmFrame->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->configPanel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

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
    delete t;
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
 * @brief Setter of the current map
 * @param map Map to use
 */
void CentralWidget::setCurrentMap(HeightMap *map)
{
    this->currentMap = map;
}

/**
 * @brief Adds a config to the list of configs
 * @param config Config to add
 */
void CentralWidget::addConfig(Config *config)
{
    this->configs.append(config);
    this->currentMap = new HeightMap(this->NAME, this->WIDTH, this->HEIGHT, this->START_POINT, this->END_POINT);
    //emit clearImage(0);
}


/**
 * @brief Starts the simulations for each configuration
 */
void CentralWidget::start()
{

    t = new ThreadGenerator(this, this->configs);
    connect(this, SIGNAL(startThread()), t, SLOT(start()));
    connect(this, SIGNAL(skipSimulation()), t, SLOT(skipToNext()));
    connect(this, SIGNAL(stopThread()), t, SLOT(stop()));
    connect(t, SIGNAL(finished()), this, SLOT(receiveUpdateImage()));
    connect(this->hmFrame->getHeightMapViewPanel(), SIGNAL(lastVertexDrawn(Vertex*)), this->t, SLOT(getVertexDrawn(Vertex*)));
    emit startThread();
    //t.start();
}

/**
 * @brief Displays a message signaling the simulations are done
 */
void CentralWidget::done()
{
    emit emitDone();
    QMessageBox doneBox(QMessageBox::Information, "Done",
                        "All simulations are done", QMessageBox::Close);
    doneBox.exec();
    t->disconnect();
    delete t;
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

/**
 * @brief Receives the signal to clear the image
 * @param count Expected number of vertices to draw
 */
void CentralWidget::receiveClearImage(int count)
{
    emit clearImage(count);
}

/**
 * @brief Receives the signal that will trigger a saving of the image drawn into the heightmap
 */
void CentralWidget::receiveImageToHeightMap()
{
    this->hmFrame->getHeightMapViewPanel()->drawImageOnHeightMap();
}

/**
 * @brief Receives the signal stating if modifications on the heightmap are allowed
 * @param b Modifications allowed or not
 */
void CentralWidget::receiveModifAllowed(bool b){
    emit emitModifAllowed(b);
}

/**
 * @brief Receive the signal telling the generation thread to go to the next simulation
 */
void CentralWidget::nextSimulation()
{
    emit skipSimulation();
}

/**
 * @brief Receive the signal telling the generation thread to stop the generation
 */
void CentralWidget::stop()
{
    emit stopThread();
}

/**
 * @brief Returns the number of configs in the vector
 * @return The number of configs
 */
int CentralWidget::getNbConfigs()
{
    this->nbConfigs++;
    return this->nbConfigs;
}

/**
 * @brief Removes a config to the list of configs to run
 * @param index Index of the config to remove
 */
void CentralWidget::removeConfig(int index)
{
    this->configs.removeAt(index);
    if (this->configs.isEmpty())
        this->nbConfigs = 0;
}

/**
 * @brief Deletes every config in the config list
 */
void CentralWidget::clearConfigs()
{
    this->configs.clear();
    this->nbConfigs = 0;
    this->configPanel->configChanged();
}
