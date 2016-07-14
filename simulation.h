#ifndef SIMULATION
#define SIMULATION

#include <QObject>

#include "input.h"
#include "graphwindow.h"

class Simulation : public QObject
{
    Q_OBJECT

public:
    Simulation(Input* input, GraphWindow *_graph_win);
    ~Simulation();

public slots:
    void start(); //start simulation
    void stop(); //stop simulation
    void startDrawing();

signals:
    void render(); //tell drawing widget to render
    void finished(); //perform extra work after finished
    void addGraph(GRAPHS _graph, ALG_VARIANT _alg, Qt::GlobalColor color, QCPAxis* x = 0, QCPAxis* y = 0);
    void setData(GRAPHS graph, ALG_VARIANT _alg, QVector<double> key, QVector<double> value);
    void addData(GRAPHS _graph, ALG_VARIANT _alg, double key, double value);

private:
    void connectSignalSlot();

    GraphWindow* graph_win;

    bool is_running;
    bool is_drawing;
    Input* input;

    double getMax(const vector<Node>& nodes, ALG_VARIANT _alg);
    double getTotal(const vector<Node>& nodes, ALG_VARIANT _alg);
    double getAvg(const vector<Node> &nodes, ALG_VARIANT _alg);
};

#endif // SIMULATION

