#include <QApplication>
#include <QThread>
#include <QTime>
#include <assert.h>

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
    qRegisterMetaType<std::string>("string");
    //connect(this, SIGNAL(addGraph(GRAPHS,ALG_VARIANT,Qt::GlobalColor,string,QCPAxis*,QCPAxis*))

    connect(this, SIGNAL(addGraph(GRAPHS, ALG_VARIANT, Qt::GlobalColor, string, QCPAxis*, QCPAxis*)),
            graph_win, SLOT(addGraph(GRAPHS,ALG_VARIANT, Qt::GlobalColor, string, QCPAxis*, QCPAxis*)));
    connect(this, SIGNAL(addData(GRAPHS,ALG_VARIANT,double,double)),
            graph_win, SLOT(addGraphData(GRAPHS,ALG_VARIANT,double,double)));
}

void Simulation::start()
{
    is_running = true;

    float interval = input->interval_length;

    double sim_time = 0.0;
    double interval_elapsed = 0.0;

    while(is_running)
    {
        interval_elapsed = 0.0;
        cout << "next interval" << endl;
        for(Node& n : input->nodes)
        {
            input->nextRandomPosition(n.pos_at_ti, n.pos_at_ti1, input->direction_factor, n.velocity,
                                      n.velocity, interval/1000);
        }

        emit render();

        Algorithm::broadcastTree(input->nodes, input->getSourceIndex());

        Algorithm::orderAsDepth(input->nodes, input->getSourceIndex());

        for(AlgModel* alg : input->algos)
        {
            alg->execute(input->nodes, 0.0, interval, sim_time);
        }
        while(interval - interval_elapsed >= 0) //runs for given time interval
        {
            for(Node& n : input->nodes)
            {
                float dist = Tools::distance(n.pos_at_ti, n.pos_at_ti1);
                float d = interval_elapsed * dist / interval;
                assert(d>=0 && "distance between two position in simulation cpp");

                n.pos = Tools::pointOnLineSegmentInGivenDirection(n.pos_at_ti, n.pos_at_ti1, d );

                for(AlgModel* alg : input->algos)
                {
                    n.updateRangeAt(alg->alg, sim_time/1000, interval_elapsed/1000);
                }
            }

            emit render();

            QThread::msleep(500);

            const int advanced = 200;
            interval_elapsed += advanced;
            sim_time +=advanced;

            if(is_drawing)
            {
                for(AlgModel* alg : input->algos){
                    emit addData(MAX_RANGE, alg->alg, (sim_time-advanced)/1000,
                                 getMax(input->nodes, alg->alg)/1000);
                                 //input->nodes[input->getSourceIndex()].currentRange(alg->alg));
                //for(AlgModel* alg : input->algos)
                    emit addData(TOTAL_SUM_RANGE, alg->alg, (sim_time-advanced)/1000,
                                 getTotal(input->nodes, alg->alg)/1000);
                //for(AlgModel* alg : input->algos)
                    emit addData(AVG_RANGE, alg->alg, (sim_time-advanced)/1000,
                                 getAvg(input->nodes, alg->alg)/1000);
                }
            }
        }
        //ToDo : if "stop" pressed -> stops after current interval is processed
        qApp->processEvents();


        if(!is_running)
            break;

    }

}

/*
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
                input->nextRandomPosition(n.pos, n.direction, input->direction_factor, n.velocity, diff_time);
                for(AlgModel* alg : input->algos)
                {
                    n.updateRangeAt(alg->alg, past_interval);
                }
            }
            cout << "---" << endl;

            emit render();

            QThread::msleep(500);


            if(is_drawing)
            {
                for(AlgModel* alg : input->algos)
                    emit addData(MAX_RANGE, alg->alg, new_time/1000,
                                 getMax(input->nodes, alg->alg)/1000);
                                 //input->nodes[input->getSourceIndex()].currentRange(alg->alg));
                for(AlgModel* alg : input->algos)
                    emit addData(TOTAL_SUM_RANGE, alg->alg, new_time/1000,
                                 getTotal(input->nodes, alg->alg)/1000);
                for(AlgModel* alg : input->algos)
                    emit addData(AVG_RANGE, alg->alg, new_time/1000,
                                 getAvg(input->nodes, alg->alg)/1000);
            }

            prev_time = new_time;
        }
        //ToDo : if "stop" pressed -> stops after current interval is processed
        qApp->processEvents();

        for(Node& n : input->nodes)
        {
            n.direction.first = n.direction.second;
            n.direction.second = n.pos;
        }

        if(!is_running)
            break;

        interval_exceeded = timer_interval->elapsed() - interval;
    }

}
*/

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

double Simulation::getAvg(const vector<Node> &nodes, ALG_VARIANT _alg)
{
    double total_power = 0;

    for(const Node& n: nodes)
    {
        total_power += n.getPower(_alg);
    }
    return total_power/(double)nodes.size();
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
        emit addGraph(MAX_RANGE, alg->alg, alg->graph_color, "energy (MAX)");
        //emit setData(MAX_RANGE, alg->alg, );
    }
    for(AlgModel* alg : input->algos)
    {
        emit addGraph(TOTAL_SUM_RANGE, alg->alg, alg->graph_color, "energy (TOTAL)");
    }
    for(AlgModel* alg : input->algos)
    {
        emit addGraph(AVG_RANGE, alg->alg, alg->graph_color, "energy (AVG)");
    }
}

Simulation::~Simulation()
{
//do not delete graph_win
}

