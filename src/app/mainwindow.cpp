#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    cWidget = new CentralWidget(this);
    setCentralWidget(cWidget);
    //setFixedSize(800,600); // Should not be declared that way
}

MainWindow::~MainWindow()
{
    delete ui;
}
