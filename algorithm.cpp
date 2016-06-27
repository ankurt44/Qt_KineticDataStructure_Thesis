#include <algorithm>
#include <map>
#include <limits>

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

struct NextEventComparator
{
    bool operator()(const std::pair<Vector2f, Algorithm::SIDE>& s1, const std::pair<Vector2f, Algorithm::SIDE>& s2)
    {
        return s1.first >  s2.first;
    }
};

void Algorithm::broadcastTree(vector<Node>& nodes, int source)
{
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

void Algorithm::voronoiDiagram(vector<Node>& nodes)
{
    vector<VoronoiCell> halfPlanes;

    for(int i = 0; i < nodes.size(); i++)
    {
        for(int j = 0; j < nodes.size(); j++)
        {
            if(j == i)
                continue;
            halfPlanes.push_back(Algorithm::getHalfPlane(nodes[i], nodes[j]));
        }
        VoronoiCell* cell = NULL;
        Algorithm::halfPlaneIntersection(halfPlanes, cell);
        halfPlanes.clear();
        nodes[i].cell = *cell;
        delete cell;
    }
}

/*
VoronoiCell Algorithm::getHalfPlane(Node& node1, Node& node2)
{
    const static float TOP_Y = 5000;
    const static float BOTTOM_Y = -5000;
    const static float LEFT_X = -5000;
    const static float RIGHT_X = 5000;

    Vector2f p();

    vector<Vector2f> c;

    float x1 = node1.pos.x;
    float y1 = node1.pos.y;
    float r1 = node1.getRange();
    float x2 = node2.pos.x;
    float y2 = node2.pos.y;
    float r2 = node2.getRange();

    float denom_x = 2 * (x2-x1);
    float denom_y = 2 * (y2-y1);

    float top_x, bottom_x, left_y, right_y;
    if(denom_x != 0)
    {
    top_x = (TOP_Y - y2)*(TOP_Y - y2) - (TOP_Y - y1) * (TOP_Y - y1) - r2 * r2 + r1 * r1 + x2 * x2 - x1 * x1;
    bottom_x = (BOTTOM_Y - y2)*(BOTTOM_Y - y2) - (BOTTOM_Y - y1) * (BOTTOM_Y - y1) - r2 * r2 + r1 * r1 + x2 * x2 - x1 * x1;
    top_x/=denom_x;
    bottom_x/=denom_x;
    if(LEFT_X<=top_x && top_x<=RIGHT_X)
        c.push_back(Vector2f(top_x, TOP_Y));
    if(LEFT_X<=bottom_x && bottom_x<=RIGHT_X)
        c.push_back(Vector2f(bottom_x, BOTTOM_Y));
    }
    if(denom_y != 0)
    {
    left_y = (LEFT_X - x2)*(LEFT_X - x2) - (LEFT_X - x1) * (LEFT_X - x1) - r2 * r2 + r1 * r1 + y2 * y2 - y1 * y1;
    right_y = (RIGHT_X - x2)*(RIGHT_X - x2) - (RIGHT_X - x1) * (RIGHT_X - x1) - r2 * r2 + r1 * r1 + y2 * y2 - y1 * y1;
    left_y/=denom_y;
    right_y/=denom_y;
    if(BOTTOM_Y<=left_y && left_y<=TOP_Y)
        c.push_back(Vector2f(LEFT_X, left_y));
    if(BOTTOM_Y<=right_y && right_y<=TOP_Y)
        c.push_back(Vector2f(RIGHT_X, right_y));
    }

    //ToDo : assert that only two intersection is found;
    //assert(c.size() <= 2 && "Number of intersection points is not 2.");

    int sign = Tools::sign(Tools::crossProduct2D(c[1] - c[0], node1.pos - c[0]));

    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(LEFT_X, TOP_Y) - c[0])))
        c.push_back(Vector2f(LEFT_X, TOP_Y));
    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(LEFT_X, BOTTOM_Y) - c[0])))
        c.push_back(Vector2f(LEFT_X, BOTTOM_Y));
    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(RIGHT_X, TOP_Y) - c[0])))
        c.push_back(Vector2f(RIGHT_X, TOP_Y));
    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(RIGHT_X, BOTTOM_Y) - c[0])))
        c.push_back(Vector2f(RIGHT_X, BOTTOM_Y));

    VoronoiCell* cell;
    Algorithm::convertToVoronoiCell(c, cell);
    VoronoiCell res = *cell;
    delete cell;
    return res;

}
*/

VoronoiCell Algorithm::getHalfPlane(Node &node1, Node &node2)
{
    //find point on line segment node1-node2
    /*
     *dist of point is dist*param from node1, and (1-param)*dist from node2
     *using equality of tangent length, find param
     * point = node1.pos + t*(node2.pos - node1.pos)
     */
    double param;
    {
    double dist = Tools::distance(node1.pos, node2.pos);
    double dist_sq = dist * dist;
    double r1_sq = node1.getRange() * node1.getRange();
    double r2_sq = node2.getRange() * node2.getRange();

    param = ((r1_sq - r2_sq) + dist_sq)/ (2 *dist_sq);
    }

    Vector2f point = node1.pos + (node2.pos - node1.pos) * param;

    //calculate slope line connecting node1 and node2
    double slope_12 = Tools::slopeOfLine(node1.pos, node2.pos);

    vector<Vector2f> c;

    //find intersection to boundary lines of bb
    //using eq of line with slope -1/slope_12  and passing through point
    double inf = std::numeric_limits<float>::max();
    double top_x = inf, bottom_x = inf, left_y = inf, right_y = inf;
    if((node2.pos.x - node1.pos.x) != 0) //line joining node1, node2 is vertical
                                        //no intersection  with horizontal boundary of bb
    {
        top_x = -slope_12 * (TOP_Y - point.y) + point.x;
        if(LEFT_X <= top_x && top_x <= RIGHT_X) c.push_back(Vector2f(top_x, TOP_Y));
        bottom_x = -slope_12 * (BOTTOM_Y - point.y) + point.x;
        if(LEFT_X <= bottom_x && bottom_x <= RIGHT_X) c.push_back(Vector2f(bottom_x, BOTTOM_Y));
    }
    if(slope_12 != 0)
    {
        left_y = (-1/slope_12 ) * (LEFT_X - point.x) + point.y;
        if(BOTTOM_Y <= left_y && left_y <= TOP_Y) c.push_back(Vector2f(LEFT_X, left_y));
        right_y = (-1/slope_12 ) * (RIGHT_X - point.x) + point.y;
        if(BOTTOM_Y <= right_y && right_y <= TOP_Y) c.push_back(Vector2f(RIGHT_X, right_y));
    }

    int sign = Tools::sign(Tools::crossProduct2D(c[1] - c[0], node1.pos - c[0]));

    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(LEFT_X, TOP_Y) - c[0])))
        c.push_back(Vector2f(LEFT_X, TOP_Y));
    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(LEFT_X, BOTTOM_Y) - c[0])))
        c.push_back(Vector2f(LEFT_X, BOTTOM_Y));
    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(RIGHT_X, TOP_Y) - c[0])))
        c.push_back(Vector2f(RIGHT_X, TOP_Y));
    if(sign == Tools::sign(Tools::crossProduct2D(c[1] - c[0], Vector2f(RIGHT_X, BOTTOM_Y) - c[0])))
        c.push_back(Vector2f(RIGHT_X, BOTTOM_Y));

    VoronoiCell* cell;
    Algorithm::convertToVoronoiCell(c, cell);
    VoronoiCell res = *cell;
    if(cell)
        delete cell;
    return res;

}

//recursively iterate over list of half-planes 'half_planes', and calculate intersection into 'cell'
void Algorithm::halfPlaneIntersection(const vector<VoronoiCell> _half_planes, VoronoiCell*& cell)
{
    if(_half_planes.size() == 1)
    {
        cell =  new VoronoiCell;
        *cell = _half_planes[0];
        return;
    }
    else
    {
        VoronoiCell* cell1;
        VoronoiCell* cell2;
        int mid = _half_planes.size()/2;
        vector<VoronoiCell> H1(_half_planes.begin(), _half_planes.begin()+mid);
        vector<VoronoiCell> H2(_half_planes.begin()+mid, _half_planes.end());
        halfPlaneIntersection(H1, cell1);
        halfPlaneIntersection(H2, cell2);
        halfPlaneIntersection(*cell1, *cell2, cell);
        if(cell1) delete cell1;
        if(cell2) delete cell2;
        return;
    }
}

/*
void Algorithm::halfPlaneIntersection(const VoronoiCell& v1, const VoronoiCell& v2, VoronoiCell*& cell)
{
    int left_c1 = 0;
    int right_c1 = -1;
    int left_c2 = 0;
    int right_c2 = -1;

    enum SIDE {LEFT_C1, RIGHT_C1, LEFT_C2, RIGHT_C2};

    Vector2f lc1 = v1.left[left_c1] ;
    Vector2f lc2 = v2.left[left_c2] ;

    SIDE side = (v1.left[left_c1] > v2.left[left_c2]) ? LEFT_C1 : LEFT_C2;

    right_c1 = (side == LEFT_C1)? -1 : 0;
    right_c2 = (side == LEFT_C2)? -1 : 0;

    vector<Vector2f> c;

    Vector2f* left_c = NULL;
    Vector2f* right_c = NULL;

    while(true)
    {
        switch(side)
        {
        case LEFT_C1:
            if(Tools::pointInMiddle(v1.left[left_c1], v2.left[left_c2], v2.left[left_c2+1], v2.right[right_c2], v2.right[right_c2+1]))
                c.push_back(v1.left[left_c1]);

            if(left_c1 < v1.left.size()-1)
            {
                if(Tools::intersectionPoint(v1.left[left_c1], v1.left[left_c1+1], v2.left[left_c2], v2.left[left_c2+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v1.left[left_c1], v1.left[left_c1+1], v2.right[right_c2], v2.right[right_c2+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        case RIGHT_C1:
            if(Tools::pointInMiddle(v1.right[right_c1], v2.left[left_c2], v2.left[left_c2+1], v2.right[right_c2], v2.right[right_c2+1]))
                c.push_back(v1.right[right_c1]);

            if(right_c1 < v1.right.size()-1)
            {
                if(Tools::intersectionPoint(v1.right[right_c1], v1.right[right_c1+1], v2.left[left_c2], v2.left[left_c2+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v1.right[right_c1], v1.right[right_c1+1], v2.right[right_c2], v2.right[right_c2+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        case LEFT_C2:
            if(Tools::pointInMiddle(v2.left[left_c2], v1.left[left_c1], v1.left[left_c1+1], v1.right[right_c1], v1.right[right_c1+1]))
                c.push_back(v2.left[left_c2]);

            if(left_c2 < v2.left.size()-1)
            {
                if(Tools::intersectionPoint(v2.left[left_c2], v2.left[left_c2+1], v1.left[left_c1], v1.left[left_c1+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v2.left[left_c2], v2.left[left_c2+1], v1.right[right_c1], v1.right[right_c1+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        case RIGHT_C2:
            if(Tools::pointInMiddle(v2.right[right_c2], v1.left[left_c1], v1.left[left_c1+1], v1.right[right_c1], v1.right[right_c1+1]))
                c.push_back(v2.right[right_c2]);

            if(right_c2 < v2.right.size())
            {
                if(Tools::intersectionPoint(v2.right[right_c2], v2.right[right_c2+1], v1.left[left_c1], v1.left[left_c1+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v2.right[right_c2], v2.right[right_c2+1], v1.right[right_c1], v1.right[right_c1+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        }

        //find next event point
        side = (v1.left[left_c1+1] < v1.right[right_c1+1]) ? LEFT_C1 : RIGHT_C1;
        side = (v2.left[left_c2+1] < v1.left[left_c1+1] && v2.left[left_c2+1] < v1.right[right_c1+1]) ? LEFT_C2 : side;
        side = (v2.right[right_c2+1] < v2.left[left_c2+1] && v2.right[right_c2+1] < v1.left[left_c1+1]
                && v2.right[right_c2+1] < v1.right[right_c1+1]) ? RIGHT_C2 : side;

        if(left_c1 == v1.left.size()-1 || right_c1 == v1.right.size()-1 || left_c2 == v2.left.size()-1 || right_c2 == v2.right.size()-1)
            break;

        switch(side)
        {
            case LEFT_C1: left_c1++; break;
            case RIGHT_C1: right_c1++; break;
            case LEFT_C2: left_c2++; break;
            case RIGHT_C2: right_c2++; break;
        }

        delete left_c;
        delete right_c;
    }

    Algorithm::convertToVoronoiCell(c, cell);
}
*/

void Algorithm::halfPlaneIntersection(const VoronoiCell& v1, const VoronoiCell& v2, VoronoiCell*& cell)
{
    int left_c1 = -1, right_c1 = -1, left_c2 = -1, right_c2 = -1;

    SIDE side = (v1.left[left_c1+1] < v2.left[left_c2+1]) ? LEFT_C1 : LEFT_C2;

    left_c1 = (side == LEFT_C1)? 0:-1;
    right_c1 = (side == LEFT_C1)? 0:-1;
    left_c2 = (side == LEFT_C2)? 0:-1;
    right_c2 = (side == LEFT_C2)? 0:-1;

    vector<Vector2f> c;

    vector<pair<Vector2f, SIDE> > next_event; //keep next four possible event points on the halfplane boundary
    next_event.push_back(std::make_pair(v1.left[left_c1+1], LEFT_C1));
    next_event.push_back(std::make_pair(v1.right[right_c1+1], RIGHT_C1));
    next_event.push_back(std::make_pair(v2.left[left_c2+1], LEFT_C2));
    next_event.push_back(std::make_pair(v2.right[right_c2+1], RIGHT_C2));

    std::make_heap(next_event.begin(), next_event.end(), NextEventComparator());


    Vector2f* left_c = NULL;
    Vector2f* right_c = NULL;

    while(true)
    {
        if(left_c1 == v1.left.size()-1 || right_c1 == v1.right.size()-1 || left_c2 == v2.left.size()-1 || right_c2 == v2.right.size()-1)
            break;

        std::pop_heap(next_event.begin(), next_event.end());
        side = next_event[next_event.size()-1].second;
        next_event.pop_back();
        std::make_heap(next_event.begin(), next_event.end(), NextEventComparator()); //ToDo : check if required
        switch(side)
        {
            case LEFT_C1 : left_c1++; next_event.push_back(std::make_pair(v1.left[left_c1+1], LEFT_C1));
                            std::push_heap(next_event.begin(), next_event.end(), NextEventComparator());
                            break;
            case RIGHT_C1 : right_c1++; next_event.push_back(std::make_pair(v1.right[right_c1+1], RIGHT_C1));
                            std::push_heap(next_event.begin(), next_event.end(), NextEventComparator());
                            break;
            case LEFT_C2 : left_c2++; next_event.push_back(std::make_pair(v2.left[left_c2+1], LEFT_C2));
                            std::push_heap(next_event.begin(), next_event.end(), NextEventComparator());
                            break;
            case RIGHT_C2 : right_c2++; next_event.push_back(std::make_pair(v2.right[right_c2+1], RIGHT_C2));
                            std::push_heap(next_event.begin(), next_event.end(), NextEventComparator());
                            break;
        }

        if((left_c1 == -1 && right_c1 == -1) || (left_c2 == -1 && right_c2 == -1))
            continue;

        switch(side)
        {
        case LEFT_C1:
            if(Tools::pointInMiddle(v1.left[left_c1], v2.left[left_c2], v2.left[left_c2+1], v2.right[right_c2], v2.right[right_c2+1]))
                c.push_back(v1.left[left_c1]);

            if(left_c1 < v1.left.size()-1)
            {
                if(Tools::intersectionPoint(v1.left[left_c1], v1.left[left_c1+1], v2.left[left_c2], v2.left[left_c2+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v1.left[left_c1], v1.left[left_c1+1], v2.right[right_c2], v2.right[right_c2+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        case RIGHT_C1:
            if(Tools::pointInMiddle(v1.right[right_c1], v2.left[left_c2], v2.left[left_c2+1], v2.right[right_c2], v2.right[right_c2+1]))
                c.push_back(v1.right[right_c1]);

            if(right_c1 < v1.right.size()-1)
            {
                if(Tools::intersectionPoint(v1.right[right_c1], v1.right[right_c1+1], v2.left[left_c2], v2.left[left_c2+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v1.right[right_c1], v1.right[right_c1+1], v2.right[right_c2], v2.right[right_c2+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        case LEFT_C2:
            if(Tools::pointInMiddle(v2.left[left_c2], v1.left[left_c1], v1.left[left_c1+1], v1.right[right_c1], v1.right[right_c1+1]))
                c.push_back(v2.left[left_c2]);

            if(left_c2 < v2.left.size()-1)
            {
                if(Tools::intersectionPoint(v2.left[left_c2], v2.left[left_c2+1], v1.left[left_c1], v1.left[left_c1+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v2.left[left_c2], v2.left[left_c2+1], v1.right[right_c1], v1.right[right_c1+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        case RIGHT_C2:
            if(Tools::pointInMiddle(v2.right[right_c2], v1.left[left_c1], v1.left[left_c1+1], v1.right[right_c1], v1.right[right_c1+1]))
                c.push_back(v2.right[right_c2]);

            if(right_c2 < v2.right.size()-1)
            {
                if(Tools::intersectionPoint(v2.right[right_c2], v2.right[right_c2+1], v1.left[left_c1], v1.left[left_c1+1], left_c))
                    c.push_back(*left_c);
                if(Tools::intersectionPoint(v2.right[right_c2], v2.right[right_c2+1], v1.right[right_c1], v1.right[right_c1+1], right_c))
                    c.push_back(*right_c);
            }
            break;
        }

        delete left_c;
        delete right_c;
    }

    Algorithm::convertToVoronoiCell(c, cell);
}

//convert list of coordinated 'c' to voronoi cell 'cell' representation
void Algorithm::convertToVoronoiCell(vector<Vector2f>& c, VoronoiCell*& cell)
{
    sort(c.begin(), c.end());//, sort_decreasing());
    //sort(c.begin(), c.end(), std::greater<Vector2f>());
    c.erase(unique(c.begin(), c.end()), c.end());

    cell = new VoronoiCell;

    cell->left.push_back(c[0]);
    cell->right.push_back(c[0]);
    for(int i = 1; i < c.size()-1; i++)
    {
        int sign = Tools::sign(Tools::crossProduct2D(c[i]-c[0], c[c.size()-1] - c[0]));
        if( sign >= 0)
            cell->right.push_back(c[i]);
        else
            cell->left.push_back(c[i]);
    }
    cell->left.push_back(c[c.size()-1]);
    cell->right.push_back(c[c.size()-1]);
}

