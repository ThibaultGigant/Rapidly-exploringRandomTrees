#include "runbuttonswidget.h"
#include "../configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
RunButtonsWidget::RunButtonsWidget(QWidget *parent) : QFrame(parent)
{
    this->cp = (ConfigPanel *) parent;
    this->cw = cp->getCentralWidget();

    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->addButton = new QPushButton("Add to list");
    this->runButton = new QPushButton("Add and Run");

    // Adding widgets to the layout
    this->layout->addWidget(this->addButton);
    this->layout->addWidget(this->runButton);

    // Displaying the layout
    this->setLayout(this->layout);

    // Connections
    connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(receiveImageToHeightMap()));
    connect(this->addButton, SIGNAL(clicked(bool)), this->cp, SLOT(addConfig()));
    connect(this->runButton, SIGNAL(clicked(bool)), this->cp, SLOT(addConfig()));
    connect(this->runButton, SIGNAL(clicked(bool)), this->cp, SLOT(start()));
    connect(this->runButton, SIGNAL(clicked(bool)), this, SLOT(toRun()));
    connect(this, SIGNAL(isRunning(bool)), this->cw, SLOT(receiveModifAllowed(bool)));
    connect(this->cw, SIGNAL(emitDone()), this, SLOT(toStop()));
}

/**
 * @brief Destructor
 */
RunButtonsWidget::~RunButtonsWidget()
{
    delete addButton;
    delete runButton;
    delete layout;
}

/**
 * @brief Receives a signal to change the buttons to Next and Stop buttons
 */
void RunButtonsWidget::toRun()
{
    this->isRun(true);
}

/**
 * @brief Receives a signal to change the buttons to default buttons (Add and Run)
 */
void RunButtonsWidget::toStop()
{
    this->isRun(false);
}

/**
 * @brief Changes the buttons according to the status : running or not
 * @param b Boolean stating if ther's a simulation running or not
 */
void RunButtonsWidget::isRun(bool b)
{
    emit isRunning(!b);
    this->addButton->disconnect();
    this->runButton->disconnect();

    if (b)
    {
        this->addButton->setText("Next run");
        this->runButton->setText("Stop all runs");

        connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(nextSimulation()));
        connect(this->runButton, SIGNAL(clicked(bool)), this->cw, SLOT(stop()));
        connect(this->runButton, SIGNAL(clicked(bool)), this, SLOT(toStop()));
    }
    else
    {
        this->addButton->setText("Add to list");
        this->runButton->setText("Run");

        // Connections
        connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(receiveImageToHeightMap()));
        connect(this->addButton, SIGNAL(clicked(bool)), this->cp, SLOT(addConfig()));
        connect(this->runButton, SIGNAL(clicked(bool)), this->cp, SLOT(start()));
        connect(this->runButton, SIGNAL(clicked(bool)), this, SLOT(toRun()));
    }
}

/**
 * @brief Sets the run button to "Add and Run"
 */
void RunButtonsWidget::isModified(bool toUpdate)
{
    this->runButton->disconnect();
    connect(this->runButton, SIGNAL(clicked(bool)), this->cp, SLOT(addConfig()));
    connect(this->runButton, SIGNAL(clicked(bool)), this->cp, SLOT(start()));
    connect(this->runButton, SIGNAL(clicked(bool)), this, SLOT(toRun()));
    this->runButton->setText("Add and Run");

    if (toUpdate)
        this->addButton->setText("Update");
    else
        this->addButton->setText("Add to list");
}

/**
 * @brief Sets the run button to "Run"
 */
void RunButtonsWidget::isNotModified()
{
    disconnect(this->runButton, SIGNAL(clicked(bool)), this->cp, SLOT(addConfig()));
    this->runButton->setText("Run");

    this->addButton->setText("Add to list");
}
