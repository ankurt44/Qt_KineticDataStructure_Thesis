#include <map>

#include "algbroadcastdirect.h"
#include "node.h"

AlgBroadcastDirect::AlgBroadcastDirect()
{
    alg = DIRECT_RANGE_ASSIGN;
}

void AlgBroadcastDirect::execute(vector<Node>& nodes, float interval_start, float interval_end)
{
    vector<pair<float, float> > i;
    for(Node& n : nodes)
    {
        const Node* far_child = n.getFarChild();

        if(far_child)
        {
            vector<pair<float, float> > i;

            float dist = Tools::distance(n.pos, far_child->pos);
            i.push_back(make_pair(interval_start, dist));
            float buffer = 2 * n.velocity * (interval_end - interval_start);
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
