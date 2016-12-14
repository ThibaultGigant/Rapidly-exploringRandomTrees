#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Config *config = new Config();
    MainWindow *w = new MainWindow(NULL, config);
    w->show();

    return a.exec();
}
