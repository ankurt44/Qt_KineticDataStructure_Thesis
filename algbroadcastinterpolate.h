#ifndef ALGBROADCAST
#define ALGBROADCAST

#include "algmodel.h"

class AlgBroadcastInterpolate : public AlgModel
{
public:

    AlgBroadcastInterpolate(string name, Qt::PenStyle linestyle);

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end, float m_passed_time) override;
};

#endif // ALGBROADCAST

