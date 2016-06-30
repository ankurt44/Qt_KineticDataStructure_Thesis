#ifndef ALGMODEL
#define ALGMODEL

#include "node.h"
#include "alg.h"

class AlgModel
{
public:
    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end) = 0;

    ALG_VARIANT alg;
};

#endif // ALGMODEL

