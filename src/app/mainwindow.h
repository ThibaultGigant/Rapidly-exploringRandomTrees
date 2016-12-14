#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <iostream>
#include "heightmapframe.h"
#include "centralwidget.h"
#include "../classes/config.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Config *config = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CentralWidget *cWidget;
    Config * config;

};

#endif // MAINWINDOW_H
