#include "responsiblenodes.h"

vector<int> ResponsibleNodes::getAllSmallerOrder(const vector<Node>& _nodes, int _curr_node)
{
    vector<int> prev_nodes;
    for(int i = 0; i < _nodes.size(); i++)
    {
        if(_nodes[i].order < _nodes[_curr_node].order)
            prev_nodes.push_back(i);
    }
    return prev_nodes;
}

vector<int> ResponsibleNodes::getTwoCloserNodes(const vector<Node>& _nodes, int _curr_node)
{
    vector<int> closer_nodes_i;

    vector<Node> closer_nodes;
    for(int i = 0; i < _nodes.size(); i++)
    {
        if(_nodes[i].order < _nodes[_curr_node].order)
        {
            closer_nodes_i.push_back(i);
            closer_nodes.push_back(_nodes[i]);
        }
    }

    int _i = 0;
    int closer_i = 0;
    for(int i = 0; i < closer_nodes.size(); i++)
    {
        if(Tools::distance(_nodes[_curr_node].pos, closer_nodes[i].pos) < Tools::distance(_nodes[_curr_node].pos, _nodes[_i].pos))
            _i = i;
    }
    closer_i = closer_nodes_i[_i];

    closer_nodes_i.clear();
    closer_nodes_i.push_back(closer_i);
    return closer_nodes_i;
}
