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
    QString NAME = "Default Map";
    QPointF START_POINT = QPointF (WIDTH / 2, HEIGHT / 2);
    QPointF END_POINT = QPointF (0, 0);

    // Constructor-Destructor
    explicit CentralWidget(QWidget *parent = 0);
    ~CentralWidget();

    // Getters and setters
    HeightMap *getCurrentMap();
    void setCurrentMap(HeightMap *map);

    // Other
    void addConfig(Config *config);
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

signals:
    void emitDrawElement(Vertex *vertex);
    void emitUpdateImage();
    void startThread();
    void stopThread();
    void clearImage(int count);
    void emitModifAllowed(bool b);

public slots:
    void receiveDrawElement(Vertex *vertex);
    void receiveUpdateImage();
    void receiveClearImage(int count = 0);
    void receiveImageToHeightMap();
    void done();
    void receiveModifAllowed(bool b);
    void stop();
};

#endif // CENTRALWIDGET_H
