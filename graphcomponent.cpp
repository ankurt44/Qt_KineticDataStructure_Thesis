#include <iostream>

#include "graphcomponent.h"

GraphComponent::GraphComponent(QWidget *parent)
    :QCustomPlot(parent)
{

}

void GraphComponent::addGraph(ALG_VARIANT _alg, Qt::GlobalColor color, Qt::PenStyle linestyle, string vAxis,
                              QCPAxis *keyAxis, QCPAxis *valueAxis, string name)
{
    if(graphs.find(_alg) != graphs.end())
    {
        std::cout << "graph already added to graph component :" << _alg << endl;
        return;
    }

    graphs.insert(std::make_pair(_alg, QCustomPlot::addGraph(keyAxis, valueAxis)));
    QCustomPlot::xAxis->setLabel("time");
    QCustomPlot::yAxis->setLabel(QString::fromStdString(vAxis));

    QPen pen;
    pen.setColor(color);
    pen.setStyle(linestyle);
    graphs.find(_alg)->second->setPen(pen);
    //graphs.find(_alg)->second->setLineStyle(QCPGraph::lsLine);
    graphs.find(_alg)->second->setName(QString::fromStdString(name));
    //graphs.find(_alg)->second->setScatterStyle(QCPScatterStyle::ssDisc);
    QCustomPlot::legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setBold(true);
    legendFont.setPointSize(10);
    QCustomPlot::legend->setFont(legendFont);
    QCustomPlot::legend->setSelectedFont(legendFont);
    QCustomPlot::legend->setMaximumSize(40,40);
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
        graphs.find(_alg)->second->rescaleValueAxis(true);
        //QCustomPlot::yAxis->setRange(value+2,500 ,Qt::AlignTop);
        QCustomPlot::xAxis->setRange(key+1 ,30 ,Qt::AlignRight);
        QCustomPlot::replot();
    }
}

void GraphComponent::removeGraph(ALG_VARIANT _alg)
{

}
