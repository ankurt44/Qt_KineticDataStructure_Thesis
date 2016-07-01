#ifndef ALGVORONOI
#define ALGVORONOI

#include "algmodel.h"

class AlgVoronoi : public AlgModel
{
public:

    AlgVoronoi();

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end) override;

    static void voronoiDiagram(vector<Node>& nodes);

    static VoronoiCell getHalfPlane(Node &node1, Node &node2);

    static void halfPlaneIntersection(const vector<VoronoiCell> _half_planes, VoronoiCell*& cell);

    static void halfPlaneIntersection(const VoronoiCell& v1, const VoronoiCell& v2, VoronoiCell*& cell);

    static void convertToVoronoiCell(vector<Vector2f>& c, VoronoiCell*& cell);

    enum SIDE {LEFT_C1, RIGHT_C1, LEFT_C2, RIGHT_C2};

};


#endif // ALGVORONOI

