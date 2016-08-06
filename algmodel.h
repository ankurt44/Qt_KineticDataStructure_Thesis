#ifndef ALGMODEL
#define ALGMODEL

#include "node.h"
#include "alg.h"

class AlgModel
{
public:

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end, float m_passed_time) = 0;

    ALG_VARIANT alg;
    string name;
    Qt::GlobalColor graph_color;
    Qt::PenStyle linestyle;
};

#endif // ALGMODEL

