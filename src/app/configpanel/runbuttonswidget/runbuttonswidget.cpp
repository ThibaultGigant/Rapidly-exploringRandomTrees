#include "runbuttonswidget.h"
#include "../configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Widget's parent
 */
RunButtonsWidget::RunButtonsWidget(QWidget *parent) : QFrame(parent)
{
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
    ConfigPanel *p = (ConfigPanel *) parent;
    this->cw = p->getCentralWidget();

    connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(receiveImageToHeightMap()));
    connect(this->addButton, SIGNAL(clicked(bool)), parent, SLOT(addConfig()));
    connect(this->runButton, SIGNAL(clicked(bool)), parent, SLOT(start()));
    connect(this, SIGNAL(isRunning(bool)), SLOT(this->cw->receiveModifAllowed(bool)));
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
 * @brief Changes the buttons according to the status : running or not
 * @param b Boolean stating if ther's a simulation running or not
 */
void RunButtonsWidget::isRun(bool b)
{
    emit isRunning(!b);
    this->addButton->disconnect();
    this->runButton->disconnect();

    if (isRunning)
    {
        this->addButton->setText("Next");
        this->runButton->setText("Stop");

        connect(this->addButton, SIGNAL(clicked(bool)), p->getCentralWidget(), SLOT(receiveImageToHeightMap()));
        connect(this->addButton, SIGNAL(clicked(bool)), parent, SLOT(addConfig()));
        connect(this->runButton, SIGNAL(clicked(bool)), parent, SLOT(start()));
    }
    else
    {
        this->addButton->setText("Add");
        this->runButton->setText("Run");

        // Connections
        connect(this->addButton, SIGNAL(clicked(bool)), this->cw, SLOT(receiveImageToHeightMap()));
        connect(this->addButton, SIGNAL(clicked(bool)), this->parent(), SLOT(addConfig()));
        connect(this->runButton, SIGNAL(clicked(bool)), this->parent(), SLOT(start()));

    }


}
