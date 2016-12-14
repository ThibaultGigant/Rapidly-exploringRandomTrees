#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "src/classes/session.h"
#include "src/classes/metrics/euclidiandistance.h"
#include "src/classes/generators/rrtgenerator.h"
#include "src/classes/endmethods/verticesnumber.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Config *config = new Config();

    qDebug() << "Avant creation session";
    Session *session;
    qDebug() << "Avant creation euclide";
    config->setMetric(new EuclidianDistance());
    qDebug() << "Avant creation generator";
    config->setGenerator(new RRTGenerator(session));
    qDebug() << "Avant creation endmethod";
    config->setEndMethod(new VerticesNumber(10));
    qDebug() << "Avant vraie creation session";
    session = new Session(5, config);
    qDebug() << "Avant mainwindow";
    MainWindow *w = new MainWindow(NULL, config);
    w->show();

    session->generate();
    return a.exec();
}
