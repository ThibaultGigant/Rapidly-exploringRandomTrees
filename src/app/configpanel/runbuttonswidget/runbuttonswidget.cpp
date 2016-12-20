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
    this->addButton = new QPushButton("Add to list");
    this->runButton = new QPushButton("Run");

    // Adding widgets to the layout
    this->layout->addWidget(this->addButton);
    this->layout->addWidget(this->runButton);

    // Displaying the layout
    this->setLayout(this->layout);

    // Connections
    ConfigPanel *p = (ConfigPanel *) parent;
    connect(this->addButton, SIGNAL(clicked(bool)), p->getCentralWidget(), SLOT(receiveImageToHeightMap()));
    connect(this->addButton, SIGNAL(clicked(bool)), parent, SLOT(addConfig()));
    connect(this->runButton, SIGNAL(clicked(bool)), parent, SLOT(start()));
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
 * @param isRunning Boolean stating if ther's a simulation running or not
 */
void RunButtonsWidget::isRun(bool isRunning)
{
    //delete widgets and connections
    this->layout->removeWidget(this->addButton);
    this->layout->removeWidget(this->runButton);
    this->addButton->disconnect();
    this->runButton->disconnect();
    delete this->addButton;
    delete this->runButton;

    if (isRunning)
    {
        this->addButton = new QPushButton("Add to list");
        this->runButton = new QPushButton("Run");

        // Adding widgets to the layout
        this->layout->addWidget(this->addButton);
        this->layout->addWidget(this->runButton);

        // Displaying the layout
        this->setLayout(this->layout);

        // Connections
        ConfigPanel *p = (ConfigPanel *) parent;
        connect(this->addButton, SIGNAL(clicked(bool)), p->getCentralWidget(), SLOT(receiveImageToHeightMap()));
        connect(this->addButton, SIGNAL(clicked(bool)), parent, SLOT(addConfig()));
        connect(this->runButton, SIGNAL(clicked(bool)), parent, SLOT(start()));
    }
    else
    {
        this->addButton = new QPushButton("Add to list");
        this->runButton = new QPushButton("Run");

        // Adding widgets to the layout
        this->layout->addWidget(this->addButton);
        this->layout->addWidget(this->runButton);

        // Displaying the layout
        this->setLayout(this->layout);

        // Connections
        ConfigPanel *p = (ConfigPanel *) parent;
        connect(this->addButton, SIGNAL(clicked(bool)), p->getCentralWidget(), SLOT(receiveImageToHeightMap()));
        connect(this->addButton, SIGNAL(clicked(bool)), parent, SLOT(addConfig()));
        connect(this->runButton, SIGNAL(clicked(bool)), parent, SLOT(start()));
    }

}
