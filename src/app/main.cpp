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
    RRTGenerator *rrt = new RRTGenerator();

    config->setMetric(new EuclidianDistance());
    config->setGenerator(rrt);
    config->setEndMethod(new VerticesNumber(10));
    Session *session = new Session(5, config);
    rrt->setSession(session);

    MainWindow *w = new MainWindow(NULL, config);
    w->show();

    session->generate();
    return a.exec();
}
