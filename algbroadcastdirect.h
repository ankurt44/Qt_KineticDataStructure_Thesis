#ifndef ALGBROADCASTDIRECT
#define ALGBROADCASTDIRECT

#include "algmodel.h"

class AlgBroadcastDirect : public AlgModel
{
public:

    AlgBroadcastDirect(string name);

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end, float m_passed_time) override;
};
#endif // ALGBROADCASTDIRECT

