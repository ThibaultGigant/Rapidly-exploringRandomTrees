#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

class ConfigPanel;

class ListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = 0);
    void addItem(const QString &label);

private:
    ConfigPanel *configPanel;

    QHBoxLayout *globalLayaout;
    QVBoxLayout *listLayout;
    QVBoxLayout *buttonsLayout;

    QListWidget *listWidget;
    QPushButton *clearButton;
    QPushButton *deleteButton;

    void mouseDoubleClickEvent(QMouseEvent *e);

signals:

public slots:
    void deleteItem();
};

#endif // LISTWIDGET_H
