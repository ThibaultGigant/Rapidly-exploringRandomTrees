#include "nbverticeslimitwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the Widget
 */
NbVerticesLimitWidget::NbVerticesLimitWidget(QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->checkBox = new QCheckBox("Maximum number of vertices");
    this->spinBox = new QSpinBox();

    // Setting spinbox values
    this->spinBox->setRange(1, 10000);
    this->spinBox->setValue(0);

    // Adding widget
    this->layout->addWidget(this->checkBox);

    // Adding the connection between the checkbox and the display of the spinbox
    connect(this->checkBox, SIGNAL(stateChanged(int)), this, SLOT(manageSpinbox(int)));
}

/**
 * @brief Destructor
 */
NbVerticesLimitWidget::~NbVerticesLimitWidget()
{
    delete checkBox;
    delete spinBox;
    delete layout;
}

/**
 * @brief Triggers the display of the spinbox allowing to choose the number of vertices to generate
 * @param toDisplay Representing if the SpinBox should be displayed or not
 */
void NbVerticesLimitWidget::manageSpinbox(int toDisplay)
{
    if (toDisplay)
        this->layout->addWidget(this->spinBox);
    else
        this->layout->removeWidget(this->spinBox);
}

/**
 * @brief Returns the choice of the user about the maximum number of vertices to generate
 * @return Maximum number of vertices to generate
 */
qint64 NbVerticesLimitWidget::getMaxNbVertices()
{
    if (this->checkBox->checkState() == Qt::Unchecked)
        return (qint64) 0;
    return (qint64) this->spinBox->value();
}
