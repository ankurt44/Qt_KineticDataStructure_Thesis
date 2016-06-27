#include <QApplication>
#include <QThread>
#include <QTime>

#include "simulation.h"
#include "algorithm.h"

Simulation::Simulation(Input* input) : input(input)
{
    is_running = false;
    //this->input = input;
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

        //1. the positions were latest updated at time 'new_time'
        //get positions at start of interval, then apply algorithms


        emit render();

        Algorithm::broadcastTree(input->nodes, input->getSourceIndex());

        //2.advance state of nodes by 'interval_exceeded' time

        while(interval - timer_interval->elapsed() - interval_exceeded > 0) //runs for given time interval
        {
            new_time =  timer_sim->elapsed();
            diff_time = (new_time - prev_time) / 1000;

            for(Node& n : input->nodes)
            {
                Tools::nextRandomPosition(n.pos, n.velocity, diff_time);
            }

            emit render();
            QThread::msleep(1000);
            qApp->processEvents();

            prev_time = new_time;
        }

        if(!is_running)
            break;

        interval_exceeded = timer_interval->elapsed() - interval;
    }

}

void Simulation::stop()
{
    is_running = false;
    emit finished();
}

Simulation::~Simulation()
{
}

