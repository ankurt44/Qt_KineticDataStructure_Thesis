#ifndef GRAPHWINDOW
#define GRAPHWINDOW

#include <QWidget>
#include <QRadioButton>

#include "graphcomponent.h"
#include "constants.h"

class GraphWindow : public QWidget
{
    Q_OBJECT

public:
    GraphWindow(QWidget* parent = 0);
    ~GraphWindow();

public slots:
    void addGraph(GRAPHS graph, ALG_VARIANT alg, Qt::GlobalColor = Qt::blue, Qt::PenStyle linestyle = Qt::SolidLine, string vAxis = "energy"
            , string name = "Graph", QCPAxis *keyAxis = 0, QCPAxis *valueAxis = 0);
    void removeGraph(GRAPHS graph, ALG_VARIANT _alg);
    void addGraphData(GRAPHS graph, ALG_VARIANT _alg, double key, double value);
    void setGraphData(GRAPHS graph, ALG_VARIANT _alg, QVector<double> key, QVector<double> value);

private:
    bool checkIfGraphExist(GRAPHS graph);

    map<GRAPHS, GraphComponent*> graph_components;
};

#endif // GRAPHWINDOW

