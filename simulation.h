#ifndef SIMULATION
#define SIMULATION

#include <QObject>
#include "input.h"

class Simulation : public QObject
{
    Q_OBJECT

public:
    Simulation(Input* input);
    ~Simulation();

public slots:
    void start(); //start simulation
    void stop(); //stop simulation

signals:
    void render(); //tell drawing widget to render
    void finished(); //perform extra work after finished

private:
    bool is_running;
    Input* input;

};

#endif // SIMULATION

