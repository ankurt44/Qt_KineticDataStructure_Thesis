#include <QPushButton>

#include <iostream>
using namespace std;

#include "graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
    :QWidget(parent)
{
    QPushButton* yo_btn = new QPushButton("I am here", this);
}

GraphWindow::~GraphWindow()
{

}

void GraphWindow::addGraph(GRAPHS graph, ALG_VARIANT _alg, QCPAxis *keyAxis, QCPAxis *valueAxis)
{
    if(checkIfGraphExist(graph))
    {
        graph_components.find(graph)->second->addGraph(_alg, keyAxis, valueAxis);
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


