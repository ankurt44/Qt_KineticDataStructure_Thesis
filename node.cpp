#include <assert.h>

#include "node.h"

/*
 * _pos_at_i will be random position before current position of the node
 *
 * _pos_at_i1 will be the current position
 *
 * _pos_at_i is just considered to be the position from where the node came when it is spawned
 *
 * in simulation, the next position is found at updated as Node::pos_at_ti1
 * and Node::pos_at_ti1 will become Node::pos_at_ti
 * and then we can interpolate Node::pos between ti and ti1
 */
Node::Node(const Vector2f& _pos_at_i, const Vector2f& _pos_at_i1, float _velocity, float _range)
{
    pos = _pos_at_i1;
    pos_at_ti = _pos_at_i;
    pos_at_ti1 = _pos_at_i1;
    velocity= _velocity;
    cell = VoronoiCell();
}

Node::Node(const Node& node)
{
    pos = node.pos;
    pos_at_ti = node.pos_at_ti;
    pos_at_ti1 = node.pos_at_ti1;
    velocity = node.velocity;
    //range = node.range;
    cell = node.cell;
    order = node.order;
    children = node.children;
    alg_range = node.alg_range;
    interpolation = node.interpolation;
}

const Node* Node::getFarChild()
{
    float dist_max = 0;
    Node* far_child = NULL;
    for(Node* n : children)
    {
        float dist = Tools::distance(this->pos_at_ti, n->pos_at_ti);
        if(dist > dist_max)
        {
                dist_max = dist;
                far_child = n;
        }
    }
    return far_child;
}

void Node::updateInitialRange(ALG_VARIANT _alg, float _time)
{
    if(alg_range.find(_alg) == alg_range.end())
        alg_range.insert(make_pair(_alg, vector<pair<float, float> >()));

    float range = Tools::distance(this->pos, this->getFarChild()->pos);

    alg_range.find(_alg)->second.push_back(make_pair(_time, range));
}

double Node::getPower(ALG_VARIANT _alg) const
{
    return C*pow(this->currentRange(_alg), FACTOR);
}

void Node::addInterpolation(ALG_VARIANT _alg, vector<pair<float, float> > _i)
{
    if(interpolation.find(_alg) != interpolation.end())
    {
        interpolation.find(_alg)->second = _i;
        return;
    }
    interpolation.insert(make_pair(_alg, _i));
}

//ToDo: linear interpolation. can allow someone to pass interpolation function pointer as argument
//                                  (default could be a function that does linear interpolation)
float Node::getRangeAt(ALG_VARIANT _alg, float _time)
{

    vector<pair<float, float> > i;
    //Note : i = interpolation[_alg]; -->this way of getting value for a key will insert new value if the key is not found

    i = interpolation.find(_alg)->second;

    if(i.size() == 0)
        return 0.0f;
    else
    {

        assert(i[0].first <= _time && _time <= i[i.size()-1].first && "=>assert to check if argument falls within interval");
    }

    for(int j = 0; j < i.size()-1; j++)
    {
        if(i[j].first <= _time && _time <= i[j+1].first)
            return i[j].second + ((_time - i[j].first) * ((i[j+1].second - i[j].second)/(i[j+1].first - i[j].first)));
    }

    return 0.0f;
}

void Node::updateRangeAt(ALG_VARIANT _alg, float _total_time, float _time)
{
    if(alg_range.find(_alg) == alg_range.end())
        alg_range.insert(make_pair(_alg, vector<pair<float, float> >()));

    float range = getRangeAt(_alg, _time);

    alg_range.find(_alg)->second.push_back(make_pair(_total_time, range));
}

float Node::currentRange(ALG_VARIANT _alg) const
{
    if(alg_range.find(_alg) ==  alg_range.end())
        return 0;

    int data_count = alg_range.find(_alg)->second.size();

    if(data_count == 0)
        return 0;

    return alg_range.find(_alg)->second[data_count-1].second;
}

vector<pair<float, float> > Node::rangeDataVector(ALG_VARIANT _alg)
{
    return alg_range.find(_alg)->second;
}


