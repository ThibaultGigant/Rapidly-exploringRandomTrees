#include "listwidget.h"
#include "src/app/configpanel/configpanel.h"
#include "src/app/centralwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget, the configpanel
 */
ListWidget::ListWidget(QWidget *parent) : QWidget(parent)
{
    this->configPanel = (ConfigPanel *) parent;

    // Initialization of layouts
    this->globalLayaout = new QHBoxLayout(this);
    this->listLayout = new QVBoxLayout();
    this->buttonsLayout = new QVBoxLayout();

    // Initialization of widgets
    this->listWidget = new QListWidget();
    this->deleteButton = new QPushButton("Delete");
    this->clearButton = new QPushButton("Clear List");

    // Adding widgets to the corresponding layout
    this->listLayout->addWidget(this->listWidget);
    this->buttonsLayout->addWidget(this->deleteButton);
    this->buttonsLayout->addWidget(this->clearButton);

    // Setting layouts
    this->globalLayaout->addLayout(this->listLayout);
    this->globalLayaout->addLayout(this->buttonsLayout);
    this->setLayout(this->globalLayaout);

    // Connection of buttons
    connect(this->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));
    connect(this->clearButton, SIGNAL(clicked(bool)), this->listWidget, SLOT(clear()));
    connect(this->clearButton, SIGNAL(clicked(bool)), this->configPanel->getCentralWidget(), SLOT(clearConfigs()));
}

/**
 * @brief Adds an item to the list
 * @param label Label of the list item to display
 */
void ListWidget::addItem(const QString &label)
{
    this->listWidget->addItem(label);
}

/**
 * @brief Deletes the selected item from the list
 */
void ListWidget::deleteItem()
{
    int index;
    if (this->listWidget->selectedItems().length() <= 0)
        return;
    index = this->listWidget->currentRow();
    this->listWidget->removeItemWidget(this->listWidget->takeItem(index));
    this->configPanel->getCentralWidget()->removeConfig(index);

}
