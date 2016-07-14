#ifndef INPUT
#define INPUT

#include "node.h"
#include "algmodel.h"

/*
 * Time in milliseconds
 */
class Input
{
public:
    vector<Node> nodes;
    float interval_length;
    float direction_factor;
    ALG_VARIANT selected_alg;


    //ToDo : register movement model
    void (*nextRandomPosition)(Vector2f& curr_pos, pair<Vector2f,Vector2f>& direction,
                               float direction_factor, double speed, double dt);

    //ToDo : register algorithms
    vector<AlgModel*> algos;


    Input(float _interval_length = 5000)
    {
        nodes = vector<Node>();
        interval_length = _interval_length; //5 secs
        source = -1;
        direction_factor = 360;
    }

    bool setSource(int _source)
    {
        if(_source >= nodes.size() || _source < 0)
            return false;

        source = _source;

        return true;
    }

    const Node* getSource()
    {
        if(source == -1)
            return NULL;

        return &nodes[source];
    }

    int getSourceIndex() const
    {
        return source;
    }

private:
    int source;

};

#endif // INPUT

