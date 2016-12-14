#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Config * config) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    this->config = config;

    cWidget = new CentralWidget(this,config);
    setCentralWidget(cWidget);
    //setFixedSize(800,600); // Should not be declared that way
}

MainWindow::~MainWindow()
{
    delete ui;
}
