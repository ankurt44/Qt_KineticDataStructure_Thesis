#ifndef INPUT
#define INPUT

#include "node.h"

/*
 * Time in milliseconds
 */
class Input
{
public:
    vector<Node> nodes;
    float interval_length;

    Input(float _interval_length = 5000)
    {
        nodes = vector<Node>();
        interval_length = _interval_length; //5 secs
        source = -1;
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

    //ToDo : register movement model

    //ToDo : register algorithms

    int getSourceIndex()
    {
        return source;
    }

private:
    int source;

};

#endif // INPUT

