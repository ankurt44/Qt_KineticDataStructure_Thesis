#ifndef NODE
#define NODE

#include <cmath>

#include "vector2f.h"
#include "voronoicell.h"
#include "tools.h"

class Node
{
public:
    const static float C = 1;
    const static float FACTOR = 2;

    Vector2f pos;
    vector<Node*> children;
    VoronoiCell cell;
    float velocity;

    Node() = default;

    Node(const Vector2f& _pos, float _velocity = 0.0f, float _range = 0.0f)
    {
        pos = _pos;
        velocity= _velocity;
        range = _range;
        cell = VoronoiCell();
    }

    Node(const Node& node)
    {
        pos = node.pos;
        velocity = node.velocity;
        range = node.range;
        cell = node.cell;
    }

    float getRange()
    {
        updateRange();
        return range;
    }

    void updateRange()
    {
        range = 0;
        for(Node* n : children)
        {
            float dist = Tools::distance(this->pos, n->pos);
            if(dist > range)
                    range = dist;
        }
    }

    double getEnergy()
    {
        return C*pow(range, FACTOR);
    }

private:
    //force to call getRange, and update range as per farthest child
    float range;

};

#endif // NODE

