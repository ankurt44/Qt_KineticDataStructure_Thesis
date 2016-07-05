#include <QApplication>
#include <QThread>
#include <QTime>

#include "simulation.h"
#include "algorithm.h"

Simulation::Simulation(Input* input, GraphWindow* _graph_win) : input(input)
{
    is_running = false;
    is_drawing = false;

    graph_win = _graph_win;

    connectSignalSlot();
    //connect(this, SIGNAL(draw(int)), graph_win, SLOT(testing()));
}
void Simulation::connectSignalSlot()
{
    qRegisterMetaType<GRAPHS>("GRAPHS");
    qRegisterMetaType<ALG_VARIANT>("ALG_VARIANT");
    qRegisterMetaType<Qt::GlobalColor>("Qt::GlobalColor");
    connect(this, SIGNAL(addGraph(GRAPHS, ALG_VARIANT, Qt::GlobalColor, QCPAxis*, QCPAxis*)),
            graph_win, SLOT(addGraph(GRAPHS,ALG_VARIANT, Qt::GlobalColor, QCPAxis*, QCPAxis*)));
    connect(this, SIGNAL(addData(GRAPHS,ALG_VARIANT,double,double)),
            graph_win, SLOT(addGraphData(GRAPHS,ALG_VARIANT,double,double)));
}

void Simulation::start()
{
    is_running = true;

    float interval = input->interval_length;

    QTime* timer_sim = new QTime;
    QTime* timer_interval = new QTime;
    timer_sim->start();
    timer_interval->start();

    double interval_exceeded = 0.0;

    while(is_running)
    {
        timer_interval->restart();

        double prev_time = timer_sim->elapsed();
        double new_time = timer_sim->elapsed();
        double diff_time = 0.0;
        double past_interval = 0.0;

        //1. the positions were latest updated at time 'new_time'
        //get positions at start of interval, then apply algorithms


        emit render();

        Algorithm::broadcastTree(input->nodes, input->getSourceIndex());

        Algorithm::orderAsDepth(input->nodes, input->getSourceIndex());

        for(AlgModel* alg : input->algos)
        {
            alg->execute(input->nodes, 0.0, input->interval_length);
        }


        //2.advance state of nodes by 'interval_exceeded' time

        while(interval - timer_interval->elapsed() - interval_exceeded > 0) //runs for given time interval
        {
            new_time =  timer_sim->elapsed();
            diff_time = (new_time - prev_time) / 1000;
            past_interval += diff_time;

            for(Node& n : input->nodes)
            {
                Tools::nextRandomPosition(n.pos, n.velocity, diff_time, 0, 360);
                for(AlgModel* alg : input->algos)
                {
                    n.updateRangeAt(alg->alg, past_interval);
                }
            }

            emit render();

            QThread::msleep(500);


            if(is_drawing)
            {
            //emit add data signal to add data to graph
                //ToDo ::: add color and style in algorithm,,, send it to graphwindow,,,
                //add methods for different graphs -- max, avg, total, median
                for(AlgModel* alg : input->algos)
                    emit addData(MAX_RANGE, alg->alg, new_time/1000,
                                 getMax(input->nodes, alg->alg)/1000);
                                 //input->nodes[input->getSourceIndex()].currentRange(alg->alg));
                for(AlgModel* alg : input->algos)
                    emit addData(TOTAL_SUM_RANGE, alg->alg, new_time/1000,
                                 getTotal(input->nodes, alg->alg)/1000);
            }

            prev_time = new_time;
        }
        //ToDo : if "stop" pressed -> stops after current interval is processed
        qApp->processEvents();

        if(!is_running)
            break;

        interval_exceeded = timer_interval->elapsed() - interval;
    }

}

double Simulation::getMax(const vector<Node>& nodes, ALG_VARIANT _alg)
{
    double max_power = nodes[0].getPower(_alg);

    double p = 0;

    for(const Node& n: nodes)
    {
        p = n.getPower(_alg);
        if(max_power < p)
            max_power = p;
    }
    return max_power;
}

double Simulation::getTotal(const vector<Node> &nodes, ALG_VARIANT _alg)
{
    double total_power = 0;

    for(const Node& n: nodes)
    {
        total_power += n.getPower(_alg);
    }
    return total_power;
}

void Simulation::stop()
{
    is_running = false;
    is_drawing = false;
    emit finished();
}

void Simulation::startDrawing()
{
    is_drawing = true;
    for(AlgModel* alg : input->algos)
    {
        emit addGraph(MAX_RANGE, alg->alg, alg->graph_color);
    }
    for(AlgModel* alg : input->algos)
    {
        emit addGraph(TOTAL_SUM_RANGE, alg->alg, alg->graph_color);
    }
}

Simulation::~Simulation()
{
//do not delete graph_win
}

