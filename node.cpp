#include <assert.h>

#include "node.h"

Node::Node(const Vector2f& _pos, float _velocity, float _range)
{
    pos = _pos;
    velocity= _velocity;
    range = _range;
    cell = VoronoiCell();
}

Node::Node(const Node& node)
{
    pos = node.pos;
    velocity = node.velocity;
    range = node.range;
    cell = node.cell;
}

float Node::getRange()
{
    //cout << range << endl;
    return range;
}

const Node* Node::getFarChild()
{
    float dist_max = 0;
    Node* far_child = NULL;
    for(Node* n : children)
    {
        float dist = Tools::distance(this->pos, n->pos);
        if(dist > dist_max)
        {
                dist_max = dist;
                far_child = n;
        }
    }
    return far_child;
}

double Node::getEnergy()
{
    return C*pow(range, FACTOR);
}

void Node::addInterpolation(ALG_VARIANT _alg, vector<pair<float, float> > _i)
{
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
        assert(i[0].first <= _time && _time <= i[i.size()-1].first && "=>assert to check if argument falls within interval");

    for(int j = 0; j < i.size()-1; j++)
    {
        if(i[j].first <= _time && _time <= i[j+1].first)
            return i[j].second + ((_time - i[j].first) * ((i[j+1].second - i[j].second)/(i[j+1].first - i[j].first)));
    }

    return 0.0f;
}

float Node::updateRangeAt(ALG_VARIANT _alg, float _time)
{
    //ToDo :: create a list for each algorithm and add ranges at times to the list also,
    range = getRangeAt(_alg, _time);
    return range;
}
