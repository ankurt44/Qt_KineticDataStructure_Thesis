#ifndef ALGORITHM
#define ALGORITHM

#include"voronoicell.h"
#include "node.h"

class Algorithm
{
public:

    static void voronoiDiagram(vector<Node>& nodes);

    static VoronoiCell getHalfPlane(Node& node1, Node& node2);

    static void halfPlaneIntersection(const vector<VoronoiCell> halfPlanes, VoronoiCell*& cell);

    static void halfPlaneIntersection(const VoronoiCell& v1, const VoronoiCell& v2, VoronoiCell*& cell);

    static void convertToVoronoiCell(vector<Vector2f>& c, VoronoiCell*& cell);

    //nodes and the position of the source node
    static void broadcastTree(vector<Node>& nodes, int source);

    enum SIDE {LEFT_C1, RIGHT_C1, LEFT_C2, RIGHT_C2};

private: //tools
    static int findMinKeyIndex(vector<float>, vector<bool>);
};

#endif // ALGORITHM

