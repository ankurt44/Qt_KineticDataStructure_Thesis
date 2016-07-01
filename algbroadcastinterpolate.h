#ifndef ALGBROADCAST
#define ALGBROADCAST

#include "algmodel.h"

class AlgBroadcastInterpolate : public AlgModel
{
public:

    AlgBroadcastInterpolate();

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end) override;
};

#endif // ALGBROADCAST

