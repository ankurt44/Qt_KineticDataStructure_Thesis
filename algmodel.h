#ifndef ALGMODEL
#define ALGMODEL

#include "node.h"
#include "alg.h"

class AlgModel
{
public:
    virtual void execute(vector<Node>& nodes, float interval_start, float interval_end) = 0;

    ALG_VARIANT alg;
};

#endif // ALGMODEL

