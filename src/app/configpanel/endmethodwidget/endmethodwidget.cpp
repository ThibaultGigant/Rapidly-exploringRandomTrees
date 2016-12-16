#include "endmethodwidget.h"

/**
 * @brief Constructor
 * @param parent Parent of the widget
 */
EndMethodWidget::EndMethodWidget(QWidget *parent) : QFrame(parent)
{
    // Creating widgets
    this->globalLayout = new QVBoxLayout(this);
    this->title = new QLabel("Choose how the algorithm should stop:", this);
    this->nbVerticesFrame = new NbVerticesLimitWidget(this);
    this->timeLimitFrame = new TimeLimitWidget(this);

    // Adding widgets to layout
    this->globalLayout->addWidget(this->title);
    this->globalLayout->addWidget(this->nbVerticesFrame);
    this->globalLayout->addWidget(this->timeLimitFrame);
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
