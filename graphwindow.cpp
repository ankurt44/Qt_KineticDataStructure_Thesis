#include <QPushButton>

#include <iostream>
#include <QHBoxLayout>
using namespace std;

#include "graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
    :QWidget(parent)
{
    QWidget* widget_central = new QWidget(this);
    //QPushButton* yo_btn = new QPushButton("I am here", this);
    QVBoxLayout* controls_vertical = new QVBoxLayout;

    QHBoxLayout* controls_layout_1 = new QHBoxLayout;
    QGroupBox* h_group_box = new QGroupBox();
    h_group_box->setLayout(controls_layout_1);

    graph_components = map<GRAPHS, GraphComponent*>();

    GraphComponent* graph_max_range = new GraphComponent(this);
    graph_max_range->setFixedSize(GRAPH_WIDTH,GRAPH_HEIGHT);
    graph_components.insert(make_pair(MAX_RANGE, graph_max_range));

    GraphComponent* graph_avg_range = new GraphComponent(this);
    graph_avg_range->setFixedSize(GRAPH_WIDTH,GRAPH_HEIGHT);
    graph_components.insert(make_pair(AVG_RANGE, graph_avg_range));

    QHBoxLayout* controls_layout_2 = new QHBoxLayout;
    QGroupBox* h_group_box_2 = new QGroupBox();
    h_group_box_2->setLayout(controls_layout_2);

    GraphComponent* graph_total_range = new GraphComponent(this);
    graph_total_range->setFixedSize(GRAPH_WIDTH,GRAPH_HEIGHT);
    graph_components.insert(make_pair(TOTAL_SUM_RANGE, graph_total_range));

    //GraphComponent* graph_median_range = new GraphComponent(this);
    //graph_median_range->setFixedSize(GRAPH_WIDTH,GRAPH_HEIGHT);
    //graph_components.insert(make_pair(MEDIAN_RANGE, graph_median_range));

    controls_layout_1->addWidget(graph_max_range);
    controls_layout_1->addWidget(graph_avg_range);

    controls_layout_2->addWidget(graph_total_range);
    //controls_layout_2->addWidget(graph_median_range);
    
    controls_vertical->addWidget(h_group_box);
    controls_vertical->addWidget(h_group_box_2);

    widget_central->setLayout(controls_vertical);
    this->setFixedSize(GRAPH_WIN_WIDTH, GRAPH_WIN_HEIGHT);
}

GraphWindow::~GraphWindow()
{

}

void GraphWindow::addGraph(GRAPHS graph, ALG_VARIANT _alg, Qt::GlobalColor color, string vAxis, string name, QCPAxis *keyAxis, QCPAxis *valueAxis)
{
    if(checkIfGraphExist(graph))
    {
        graph_components.find(graph)->second->addGraph(_alg, color, vAxis, keyAxis, valueAxis, name);
        return;
    }
    graph_components.insert(std::make_pair(graph, new GraphComponent()));
}

void GraphWindow::removeGraph(GRAPHS graph, ALG_VARIANT _alg)
{
    if(checkIfGraphExist(graph))
    {
        graph_components.find(graph)->second->removeGraph(_alg);
    }
}

void GraphWindow::addGraphData(GRAPHS graph, ALG_VARIANT _alg, double key, double value)
{
    if(checkIfGraphExist(graph))
    {
        graph_components.find(graph)->second->addGraphData(_alg, key, value);
    }
}

void GraphWindow::setGraphData(GRAPHS graph, ALG_VARIANT _alg, QVector<double> key, QVector<double> value)
{
    if(checkIfGraphExist(graph))
    {
        graph_components.find(graph)->second->setGraphData(_alg, key, value);
    }
}

//if graph component already added
bool GraphWindow::checkIfGraphExist(GRAPHS graph)
{
    if(graph_components.find(graph) !=graph_components.end())
        return true;

    return false;
}


