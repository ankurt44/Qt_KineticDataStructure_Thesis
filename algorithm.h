#ifndef ALGORITHM
#define ALGORITHM

#include"voronoicell.h"
#include "node.h"

class Algorithm
{
public:

    //nodes and the position of the source node
    static void broadcastTree(vector<Node>& nodes, int source);

    //ordering functions
    static void orderAsDepth(vector<Node>& nodes, int source);

    enum SIDE {LEFT_C1, RIGHT_C1, LEFT_C2, RIGHT_C2};

private: //tools
    static int findMinKeyIndex(vector<float>, vector<bool>);
};

#endif // ALGORITHM

