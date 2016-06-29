#ifndef ALGBROADCAST
#define ALGBROADCAST

#include "algmodel.h"

class AlgBroadcastDirect : public AlgModel
{
public:

    AlgBroadcastDirect();

    virtual void execute(vector<Node>& nodes, float interval_start, float interval_end) override;
};

#endif // ALGBROADCAST

