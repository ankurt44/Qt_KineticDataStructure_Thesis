#include <iostream>

#include "graphcomponent.h"

GraphComponent::GraphComponent(QWidget *parent)
    :QCustomPlot(parent)
{

}

void GraphComponent::addGraph(ALG_VARIANT _alg, Qt::GlobalColor color, QCPAxis *keyAxis, QCPAxis *valueAxis)
{
    if(graphs.find(_alg) != graphs.end())
    {
        std::cout << "graph already added to graph component :" << _alg << endl;
        return;
    }

    graphs.insert(std::make_pair(_alg, QCustomPlot::addGraph(keyAxis, valueAxis)));
    graphs.find(_alg)->second->setPen(QPen(color));
    graphs.find(_alg)->second->setLineStyle(QCPGraph::lsLine);
    //graphs.find(_alg)->second->setScatterStyle(QCPScatterStyle::ssDisc);
}

void GraphComponent::setGraphData(ALG_VARIANT _alg, QVector<double> key, QVector<double> value)
{
    std::map<ALG_VARIANT, QCPGraph *>::iterator it;
    it = graphs.find(_alg);
    if(it != graphs.end() && key.size() == value.size())
    {
        it->second->setData(key, value);
        QCustomPlot::replot();
    }
}

void GraphComponent::addGraphData(ALG_VARIANT _alg, double key, double value)
{
    std::map<ALG_VARIANT, QCPGraph *>::iterator it;
    it = graphs.find(_alg);
    if(it != graphs.end())
    {
        it->second->addData(key, value);
        graphs[_alg]->rescaleValueAxis(true);
        //QCustomPlot::yAxis->setRange(value+2,500 ,Qt::AlignTop);
        QCustomPlot::xAxis->setRange(key+1 ,60 ,Qt::AlignRight);
        QCustomPlot::replot();
    }
}

void GraphComponent::removeGraph(ALG_VARIANT _alg)
{

}
