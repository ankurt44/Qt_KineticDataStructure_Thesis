#include<assert.h>
#include "algvoronoi.h"

AlgVoronoi::AlgVoronoi(ALG_VARIANT _alg)
{
    alg = _alg;
    graph_color = Qt::green;
    time_gap = 10;
}

bool comp(float, float); //used to get max element in vector

void AlgVoronoi::execute(vector<Node>& nodes, float m_interval_start, float m_interval_end, float m_passed_time)
{
    //  node     time   |range values|
    map<int, map<float, vector<float> > > ranges;
    map<int, vector<pair<float, float> > > node_interpolation;

    float interval = (m_interval_end - m_interval_start)/1000;
    float increment = interval/time_gap;

    cout << "started voronoi algorithm" <<endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].order == 0)
            continue;

        vector<int> resp_nodes_i = getResponsibleNodes(nodes, i);
        vector<Node> resp_nodes;
        for(int r : resp_nodes_i)
            resp_nodes.push_back(nodes[r]);

        voronoiDiagram(resp_nodes);

        //Vector2f temp = nodes[i].pos;
        for(int r = 0; r < resp_nodes.size(); r++)
        {
            for(float t = 0; t < (float)interval+increment; t = t + increment)
            {
                vector<Vector2f> points = getPointsInCircle(resp_nodes[r].pos, resp_nodes[r].cell,
                                                            nodes[i].pos_at_ti, nodes[i].velocity*t);

                float max_range = 0;
                for(Vector2f& p : points)
                {
                    Vector2f temp = Tools::farthestPosInTime(resp_nodes[r].pos, p, resp_nodes[r].velocity, t);
                    float d = Tools::distance(p, temp);
                    if(d > max_range) max_range = d;
                }

                ranges[resp_nodes_i[r]][t].push_back(max_range);
            }
        }

    }

    cout << "interpolation voronoi algorithm" <<endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        vector<pair<float, float> > interpolation;
        for(float t = 0; t < (float)interval+increment; t= t + increment)
        {
            map<float, vector<float> > time_ranges = ranges[i];
            vector<float> rs = time_ranges[t];
            if(rs.size() == 0)
            {
                interpolation.push_back(make_pair(t, 0));
                continue;       //ToDO : check if continue required
            }

            float range = *std::max_element(rs.begin(), rs.end(), comp);
            interpolation.push_back(make_pair(t,range));
        }

        nodes[i].addInterpolation(this->alg, interpolation);
    }

    cout << "done voronoi algorithm" <<endl;
}

bool comp(float a, float b){return a < b;}

vector<int> AlgVoronoi::getResponsibleNodes(const vector<Node>& _nodes, int _curr_node)
{
    vector<int> prev_nodes;
    for(int i = 0; i < _nodes.size(); i++)
    {
        if(_nodes[i].order < _nodes[_curr_node].order)
            prev_nodes.push_back(i);
    }
    return prev_nodes;
}

vector<Vector2f> AlgVoronoi::getPointsInCircle(const Vector2f& point,
                                               const VoronoiCell& cell,
                                               Vector2f& center, float radius)
{
    vector<Vector2f> points;
    points.clear();
    points = cell.left;
    for(int i = cell.right.size()-2; i >= 0; i--)
        points.push_back(cell.right[i]);

    vector<Vector2f> in_circle_points;

    //1 if the circle remains inside the cell
    //  the range is the distance from the tangent point on circle
    //  only applies for the cell containing the tangent_point at any time....
    //  if the cell doesnt contain the center-> then it can never contain the tangent point as it goes farther from cell with t
    float d_ = Tools::distance(point, center) + radius; //used to get the tangent point on circle
                                                        //in the direction of line connecting
                                                        //point and center
    Vector2f tangent_point = Tools::pointOnLineSegmentInGivenDirection(point, center, d_);

    if(Tools::ifPointInsideConvexHull(points, tangent_point))
    {
       in_circle_points.push_back(tangent_point);
       return in_circle_points;
    }

    //2 if the tangent point is outside the cell
    //  the range is farthest intersection points (or points in side circle)
    for(int i = 0; i < points.size(); i++)
    {
        if(Tools::lieInCircle(points[i], center, radius))
            in_circle_points.push_back(points[i]);

        if(i == points.size()-1)
            break;

        vector<Vector2f> intersect_points;
        intersect_points = Tools::circleIntersectLine(center, radius, points[i], points[i+1]);
        if(intersect_points.size() > 0)
            in_circle_points.insert(in_circle_points.end(), intersect_points.begin(), intersect_points.end());
    }

    return in_circle_points;
}

struct NextEventComparator
{
    bool operator()(const std::pair<Vector2f, AlgVoronoi::SIDE>& s1, const std::pair<Vector2f, AlgVoronoi::SIDE>& s2)
    {
        return s1.first >  s2.first;
    }
};

void AlgVoronoi::voronoiDiagram(vector<Node>& nodes)
{
    vector<VoronoiCell> halfPlanes;
    if(nodes.size() == 0)
        return;
    if(nodes.size() == 1)
    {
        vector<Vector2f> c;
        c.push_back(Vector2f(LEFT_X, TOP_Y));
        c.push_back(Vector2f(LEFT_X, BOTTOM_Y));
        c.push_back(Vector2f(RIGHT_X, TOP_Y));
        c.push_back(Vector2f(RIGHT_X, BOTTOM_Y));
        VoronoiCell* cell = NULL;
        convertToVoronoiCell(c, cell);
        nodes[0].cell = *cell;
        delete cell;
        return;
    }

    for(int i = 0; i < nodes.size(); i++)
    {
        for(int j = 0; j < nodes.size(); j++)
        {
            if(j == i)
                continue;
            halfPlanes.push_back(AlgVoronoi::getHalfPlane(nodes[i], nodes[j]));
        }
        VoronoiCell* cell = NULL;
        AlgVoronoi::halfPlaneIntersection(halfPlanes, cell);
        halfPlanes.clear();
        nodes[i].cell = *cell;
        delete cell;
    }
}

//ToDo : check if Node::pos works fine here, or it needs to be Node::pos_at_ti
VoronoiCell AlgVoronoi::getHalfPlane(Node &node1, Node &node2)
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
    double r1_sq = node1.currentRange(this->alg) * node1.currentRange(this->alg);
    double r2_sq = node2.currentRange(this->alg) * node2.currentRange(this->alg);

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
    AlgVoronoi::convertToVoronoiCell(c, cell);
    VoronoiCell res = *cell;
    if(cell)
        delete cell;
    return res;

}

//recursively iterate over list of half-planes 'half_planes', and calculate intersection into 'cell'
void AlgVoronoi::halfPlaneIntersection(const vector<VoronoiCell> _half_planes, VoronoiCell*& cell)
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

void AlgVoronoi::halfPlaneIntersection(const VoronoiCell& v1, const VoronoiCell& v2, VoronoiCell*& cell)
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

    AlgVoronoi::convertToVoronoiCell(c, cell);
}

//convert list of coordinated 'c' to voronoi cell 'cell' representation
void AlgVoronoi::convertToVoronoiCell(vector<Vector2f>& c, VoronoiCell*& cell)
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

