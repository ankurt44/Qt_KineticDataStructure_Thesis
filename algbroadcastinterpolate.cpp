#include <map>

#include "algbroadcastinterpolate.h"
#include "node.h"

AlgBroadcastInterpolate::AlgBroadcastInterpolate(string name, Qt::PenStyle linestyle)
{
    alg = NORMAL_INTERPOLATION;
    graph_color = Qt::blue;
    this->linestyle = linestyle;
    this->name = name;
}

void AlgBroadcastInterpolate::execute(vector<Node>& nodes, float m_interval_start, float m_interval_end, float m_passed_time)
{
    vector<pair<float, float> > i;

    double interval_start = m_interval_start/1000;
    double interval_end = m_interval_end/1000;

    for(Node& n : nodes)
    {
        const Node* far_child = n.getFarChild();

        if(far_child)
        {
            float dist = Tools::distance(n.pos_at_ti, far_child->pos_at_ti);
            i.push_back(make_pair(interval_start, dist));
            double interval_len = (interval_end - interval_start);
            float buffer = n.velocity * interval_len + far_child->velocity * interval_len;
            i.push_back(make_pair(interval_end, dist + buffer));
        }
        else
        {
            i.push_back(make_pair(interval_start, 0.0));
            i.push_back(make_pair(interval_end, 0.0));
        }

        n.addInterpolation(this->alg, i);
        i.clear();
    }
}
