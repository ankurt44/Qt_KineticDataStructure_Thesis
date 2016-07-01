#ifndef ALGBROADCAST
#define ALGBROADCAST

#include "algmodel.h"

class AlgBroadcastDirect : public AlgModel
{
public:

    AlgBroadcastDirect();

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end) override;
};

#endif // ALGBROADCAST

