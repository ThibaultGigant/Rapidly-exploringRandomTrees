#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <iostream>
#include "src/app/heightmappanel/heightmapframe.h"
#include "centralwidget.h"
#include "src/classes/config.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CentralWidget *cWidget;

};

#endif // MAINWINDOW_H
