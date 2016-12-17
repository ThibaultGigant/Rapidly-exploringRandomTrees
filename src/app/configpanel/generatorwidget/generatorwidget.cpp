#include "generatorwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
GeneratorWidget::GeneratorWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->title = new QLabel("Choose a tree generation algorithm :");
    this->comboBox = new QComboBox();

    // Adding items to the combobox
    this->comboBox->addItem("Random Tree Generator");
    this->comboBox->addItem("Rapidly-exploring Random Tree");

    this->comboBox->setCurrentIndex(1); // Set combobox to a default value

    // Adding widgets to layout
    this->layout->addWidget(this->title);
    this->layout->addWidget(this->comboBox);

    // Displaying the layout
    this->setLayout(this->layout);
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
 * @brief Returns the tree generator chosen by the user
 * @return TreeGenerator to use during the simulation
 */
TreeGenerator* GeneratorWidget::getGenerator()
{
    switch (this->comboBox->currentIndex()) {
    case 0:
        return new RandomTreeGenerator();
    case 1:
        return new RRTGenerator();
    default:
        return new RRTGenerator();
    }
}
