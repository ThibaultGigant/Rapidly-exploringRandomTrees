#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "src/classes/session.h"
#include "src/classes/metrics/euclidiandistance.h"
#include "src/classes/generators/rrtgenerator.h"
#include "src/classes/generators/randomtreegenerator.h"
#include "src/classes/endmethods/verticesnumber.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Config *config = new Config();
    //TreeGenerator *generator = new RandomTreeGenerator();
    TreeGenerator *generator = new RRTGenerator();

    config->setMetric(new EuclidianDistance());
    config->setGenerator(generator);
    config->setEndMethod(new VerticesNumber(1000));
    Session *session = new Session(20, config);
    generator->setSession(session);

    MainWindow *w = new MainWindow(NULL, config);
    w->show();

    session->generate();
    return a.exec();
}
