#include "generatorwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
GeneratorWidget::GeneratorWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QVBoxLayout(this);
    this->title = new QLabel("Choose a tree generation algorithm :");
    this->comboBox = new QComboBox();

    // Adding items to the combobox
    this->comboBox->addItem("Random Tree Generator");
    this->comboBox->addItem("Rapidly-exploring Random Tree");

    this->comboBox->setCurrentIndex(1); // Set combobox to a default value

    // Adding widgets to layout
    this->layout->addWidget(this->title);
    this->layout->addWidget(this->comboBox);
}

/**
 * @brief Destructor
 */
GeneratorWidget::~GeneratorWidget()
{
    delete this->title;
    delete this->comboBox;
    delete this->layout;
}

/**
 * @brief Returns the index of the tree generator chosen by the user
 * @return Index of the generator
 */
int GeneratorWidget::getGenerator()
{
    return this->comboBox->currentIndex();
}
