#ifndef GRAPHCOMPONENT
#define GRAPHCOMPONENT

#include <map>

using namespace std;

#include "qcustomplot.h"
#include "alg.h"

class GraphComponent : public QCustomPlot
{
public:
    GraphComponent(QWidget* parent = 0);
    void addGraph(ALG_VARIANT alg, Qt::GlobalColor = Qt::blue, string vAxis = "energy", QCPAxis *keyAxis = 0, QCPAxis *valueAxis = 0);
    void removeGraph(ALG_VARIANT _alg);
    void addGraphData(ALG_VARIANT _alg, double key, double value);
    void setGraphData(ALG_VARIANT _alg, QVector<double> key, QVector<double> value);

private:
    map<ALG_VARIANT, QCPGraph*> graphs;
};

#endif // GRAPHCOMPONENT

