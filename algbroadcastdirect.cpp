
#include "alg.h"
#include "algbroadcastdirect.h"

AlgBroadcastDirect::AlgBroadcastDirect(string name, Qt::PenStyle linestyle)
{
    alg = DIRECT_RANGE_ASSIGN;
    graph_color = Qt::red;
    this->linestyle = linestyle;
    this->name = name;
}

void AlgBroadcastDirect::execute(vector<Node> &nodes, float m_interval_start, float m_interval_end, float m_passed_time)
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
            float buffer = 2 * n.velocity * (interval_end - interval_start);
            i.push_back(make_pair(interval_start, dist + buffer));
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
