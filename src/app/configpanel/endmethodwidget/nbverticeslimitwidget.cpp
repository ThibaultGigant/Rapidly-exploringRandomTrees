#include "nbverticeslimitwidget.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param cp ConfigPanel, used to centralize informations about the config
 * @param parent Parent of the Widget
 */
NbVerticesLimitWidget::NbVerticesLimitWidget(ConfigPanel *cp, QWidget *parent) : QFrame(parent)
{
    // Widgets initialization
    this->layout = new QHBoxLayout(this);
    this->checkBox = new QCheckBox("Maximum number of vertices");
    this->spinBox = new QSpinBox();

    // Setting spinbox and checkbox values
    this->checkBox->setCheckState(Qt::Checked);
    this->spinBox->setRange(1, 100000);
    this->spinBox->setValue(1000);

    // Adding widget
    this->layout->addWidget(this->checkBox);
    this->layout->addWidget(this->spinBox);

    // Adding the connection between the checkbox and the display of the spinbox
    connect(this->checkBox, SIGNAL(stateChanged(int)), this, SLOT(manageSpinbox(int)));
    connect(this->checkBox, SIGNAL(stateChanged(int)), cp, SLOT(configChanged()));
    connect(this->spinBox, SIGNAL(valueChanged(int)), cp, SLOT(configChanged()));
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
    {
        this->layout->addWidget(this->spinBox);
        this->spinBox->show();
    }
    else
    {
        this->layout->removeWidget(this->spinBox);
        this->spinBox->hide();
    }
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

/**
 * @brief Sets the maximum number of vertices in the spinbox and checks the checkbox if > 0
 * @param value Value to set
 */
void NbVerticesLimitWidget::setMaxNbVertices(qint64 value)
{
    if (value > 0)
    {
        this->checkBox->setChecked(Qt::Checked);
        this->spinBox->setValue((int) value);
    }
    else
        this->checkBox->setChecked(Qt::Unchecked);
}
