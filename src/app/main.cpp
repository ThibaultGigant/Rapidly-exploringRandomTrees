#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "src/classes/session.h"
#include "src/classes/metrics/euclidiandistance.h"
#include "src/classes/generators/rrtgenerator.h"
#include "src/classes/generators/randomtreegenerator.h"
#include "src/classes/endmethods/endmethod.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}
