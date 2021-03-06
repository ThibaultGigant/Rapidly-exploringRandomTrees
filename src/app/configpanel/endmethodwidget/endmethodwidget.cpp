#include "endmethodwidget.h"
#include "src/app/configpanel/configpanel.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
EndMethodWidget::EndMethodWidget(QWidget *parent) : QFrame(parent)
{
    ConfigPanel *cp = (ConfigPanel *) parent;

    // Creating widgets
    this->globalLayout = new QVBoxLayout(this);
    this->title = new QLabel("Choose how the algorithm should stop:");
    this->nbVerticesFrame = new NbVerticesLimitWidget(cp);
    this->timeLimitFrame = new TimeLimitWidget(cp);

    // Adding widgets to layout
    this->globalLayout->addWidget(this->title);
    this->globalLayout->addWidget(this->nbVerticesFrame);
    this->globalLayout->addWidget(this->timeLimitFrame);

    // Displaying the layout
    this->setLayout(this->globalLayout);
}

EndMethodWidget::~EndMethodWidget()
{
    delete title;
    delete nbVerticesFrame;
    delete timeLimitFrame;
    delete globalLayout;
}

/**
 * @brief Returns the choice of the user about the maximum number of vertices to generate
 * @return Maximum number of vertices to generate
 */
qint64 EndMethodWidget::getMaxNbVertices()
{
    return this->nbVerticesFrame->getMaxNbVertices();
}

/**
 * @brief Returns the choice of the user about the time limit
 * @return time limit
 */
time_t EndMethodWidget::getTimeLimit()
{
    return this->timeLimitFrame->getTimeLimit();
}

/**
 * @brief Sets the maximum number of vertices in the spinbox
 */
void EndMethodWidget::setMaxNbVertices(qint64 value)
{
    this->nbVerticesFrame->setMaxNbVertices(value);
}

void EndMethodWidget::setTimeLimit(time_t value)
{
    this->timeLimitFrame->setTimeLimit(value);
}

EndMethod* EndMethodWidget::getEndMethod()
{
    return new EndMethod(this->getMaxNbVertices(), this->getTimeLimit());
}
