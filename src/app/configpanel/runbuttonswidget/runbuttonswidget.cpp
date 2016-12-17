#include "runbuttonswidget.h"

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

    // Connection to the parent
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
