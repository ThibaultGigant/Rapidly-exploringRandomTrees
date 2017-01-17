#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVector>
#include "src/classes/config.h"
#include "src/app/configpanel/configpanel.h"
#include "src/classes/heightmap.h"
#include "src/classes/session.h"

class HeightMapFrame;
class ThreadGenerator;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    // Default variables
    int WIDTH = 800;
    int HEIGHT = 800;
    QString NAME = "DefaultMapName";
    QPointF *START_POINT = new QPointF (WIDTH / 2, HEIGHT / 2);
    QPointF *END_POINT = new QPointF (0, 0);

    // Constructor-Destructor
    explicit CentralWidget(QWidget *parent = 0);
    ~CentralWidget();

    // Getters and setters
    HeightMap *getCurrentMap();
    void setCurrentMap(HeightMap *map);
    int getNbConfigs();
    QVector<Config *> getConfigs() const;

    // Other
    void addConfig(Config *config);
    void removeConfig(int index);
    void start();

private :
    // Interface
    QHBoxLayout *layout;
    HeightMapFrame *hmFrame;
    ConfigPanel *configPanel;
    // Variables
    QVector<Config*> configs;
    HeightMap *currentMap;
    ThreadGenerator *t;
    int nbConfigs;

signals:
    void emitDrawElement(Vertex *vertex);
    void emitUpdateImage();
    void startThread();
    void skipSimulation();
    void stopThread();
    void clearImage(int count);
    void emitModifAllowed(bool b);
    void emitDone();

public slots:
    void receiveDrawElement(Vertex *vertex);
    void receiveUpdateImage();
    void receiveClearImage(int count = 0);
    void receiveImageToHeightMap();
    void done();
    void receiveModifAllowed(bool b);
    void nextSimulation();
    void stop();
    void clearConfigs();
};

#endif // CENTRALWIDGET_H
