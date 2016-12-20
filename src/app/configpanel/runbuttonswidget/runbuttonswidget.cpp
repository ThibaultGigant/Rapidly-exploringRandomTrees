#include "runbuttonswidget.h"
#include "../configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
RunButtonsWidget::RunButtonsWidget(QWidget *parent) : QFrame(parent)
{
    ConfigPanel *p = (ConfigPanel *) parent;
    this->cw = p->getCentralWidget();

    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->addButton = new QPushButton("Add");
    this->runButton = new QPushButton("Run");

    // Adding widgets to the layout
    this->layout->addWidget(this->addButton);
    this->layout->addWidget(this->runButton);

    // Displaying the layout
    this->setLayout(this->layout);

    // Connections
    connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(receiveImageToHeightMap()));
    connect(this->addButton, SIGNAL(clicked(bool)), parent, SLOT(addConfig()));
    connect(this->runButton, SIGNAL(clicked(bool)), parent, SLOT(start()));
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

void RunButtonsWidget::toRun()
{
    this->isRun(true);
}

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
        this->addButton->setText("Next");
        this->runButton->setText("Stop");

        connect(this->runButton, SIGNAL(clicked(bool)), this->cw, SLOT(stop()));
        connect(this->runButton, SIGNAL(clicked(bool)), this, SLOT(toStop()));
    }
    else
    {
        this->addButton->setText("Add");
        this->runButton->setText("Run");

        // Connections
        connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(receiveImageToHeightMap()));
        connect(this->addButton, SIGNAL(clicked(bool)), this->parent(), SLOT(addConfig()));
        connect(this->runButton, SIGNAL(clicked(bool)), this->parent(), SLOT(start()));
        connect(this->runButton, SIGNAL(clicked(bool)), this, SLOT(toRun()));

    }


}
