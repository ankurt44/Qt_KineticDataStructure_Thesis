#include <algorithm>
#include <map>
#include <limits>
#include <list>

#include "algorithm.h"
#include "tools.h"
#include "constants.h"


struct SortPair
{
    bool operator()(const std::pair< pair<int, int> , int>& e1, const std::pair< pair<int, int> , int>& e2)
    {
        return e1.second < e2.second;
    }
};
/*
struct NextEventComparator
{
    bool operator()(const std::pair<Vector2f, Algorithm::SIDE>& s1, const std::pair<Vector2f, Algorithm::SIDE>& s2)
    {
        return s1.first >  s2.first;
    }
};
*/

void Algorithm::broadcastTree(vector<Node>& nodes, int source)
{

    //clear nodes children
    for(Node& n: nodes)
        n.children.clear();

    map< int,  vector<int> > edges;
    //edge_wt.push_back(std::make_pair(std::make_pair(10, 20), 30));

    for(int i = 0; i < nodes.size(); i++)
    {
        edges.insert(std::make_pair(i, vector<int>()));
        for(int j = 0; j < nodes.size(); j++)
        {
            auto it = edges.find(i);
            it->second.push_back(j);
            //it->second.push_back(std::make_pair(j,Tools::distance(Vector2f(nodes[i].pos), Vector2f(nodes[j].pos))));
        }
    }

    /*std::sort(edge_wt.begin(), edge_wt.end(), SortPair());
    //std::sort(edge_wt.begin(), edge_wt.end(), [](const std::pair< pair<int, int> , int>& e1, const std::pair< pair<int, int> , int>& e2){
    //                return e1.second < e2.second;
    //        });
    */

    vector<float> key_n(nodes.size(), std::numeric_limits<float>::max());
    vector<int> parent_n(nodes.size(), -1);
    vector<bool> if_included_n(nodes.size(), false);

    key_n[source] = 0;

    for(int i = 0; i < nodes.size(); i++)
    {
        int min_index = findMinKeyIndex(key_n, if_included_n);

        if(min_index == -1) //ToDo :: check again of this condition
            continue;

        if_included_n[min_index] = true;

        for(int i_ngbr = 0; i_ngbr < nodes.size(); i_ngbr++)
        {
            float key_ngbr = Tools::distance(nodes[min_index].pos,nodes[i_ngbr].pos);
            if(min_index!=i_ngbr && if_included_n[i_ngbr] == false && key_ngbr < key_n[i_ngbr])
                parent_n[i_ngbr] = min_index, key_n[i_ngbr] = key_ngbr;
        }
    }

    for(int i = 0; i < nodes.size(); i++)
        if(i != source)
            nodes[parent_n[i]].children.push_back(&nodes[i]);
}

int Algorithm::findMinKeyIndex(vector<float> key_n, vector<bool> if_included_n)
{
    int min_index = -1;
    float min = std::numeric_limits<float>::max();

    for(int i = 0; i < key_n.size(); i++)
        if(key_n[i] < min && if_included_n[i] == false)
            min_index = i, min = key_n[i];

    return min_index;
}

void Algorithm::orderAsDepth(vector<Node>& nodes, int source)
{
    //no need to keep track of visited node, as the input is a acyclic graph (broadcast tree)
    list<int> queue;
    queue.push_back(source);

    list<int> adj;

    int i = 0; //source node

    while(!queue.empty())
    {
        int index = queue.front();
        queue.pop_front();
        nodes[index].order = i;
        i++;

        for(Node* n : nodes[index].children)
        {
            int pos_in_vector = n - &nodes[0];
            adj.push_back(pos_in_vector);
        }
        //ToDo :: sort(adj.begin(), adj.end());

        queue.splice(queue.end(), adj);
    }

}
