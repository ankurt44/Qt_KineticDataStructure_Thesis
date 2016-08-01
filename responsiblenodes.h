#ifndef RESPONSIBLENODES
#define RESPONSIBLENODES

#include <vector>
#include "node.h"
using namespace std;

class ResponsibleNodes
{

public:
    static vector<int> getAllSmallerOrder(const vector<Node> &_nodes, int _curr_node);
    static vector<int> getTwoCloserNodes(const vector<Node> &_nodes, int _curr_node);
};

#endif // RESPONSIBLENODES

