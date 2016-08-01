#ifndef ALGVORONOI
#define ALGVORONOI

#include "algmodel.h"

class AlgVoronoi : public AlgModel
{
public:

    AlgVoronoi(ALG_VARIANT _alg,
                vector<int> (*getResponsibleNodes)(const vector<Node>& _nodes, int _curr_node)
                    ,Qt::GlobalColor graph_color ,float _direction_factor =360);

    virtual void execute(vector<Node>& nodes, float m_interval_start, float m_interval_end, float m_passed_time) override;

     void voronoiDiagram(vector<Node>& nodes);

     VoronoiCell getHalfPlane(Node &node1, Node &node2);

     void halfPlaneIntersection(const vector<VoronoiCell> _half_planes, VoronoiCell*& cell);

     void halfPlaneIntersection(const VoronoiCell& v1, const VoronoiCell& v2, VoronoiCell*& cell);

     void convertToVoronoiCell(vector<Vector2f>& c, VoronoiCell*& cell);

    enum SIDE {LEFT_C1, RIGHT_C1, LEFT_C2, RIGHT_C2};

private:
    //vector<int> getResponsibleNodes(const vector<Node>& _nodes, int _curr_node);

    vector<int> (*getResponsibleNodes)(const vector<Node>& _nodes, int _curr_node);

    vector<Vector2f> getPointsInCircle(const Vector2f &point, const VoronoiCell& cell, Vector2f& center,
                                       Vector2f& towards, float _direction_factor, float radius);

    vector<Vector2f> getPointsInArc(const Vector2f &point, const VoronoiCell &cell, Vector2f &center, Vector2f &towards,
                                    float _direction_factor, float radius);

    float time_gap;

    float direction_factor;
};


#endif // ALGVORONOI

