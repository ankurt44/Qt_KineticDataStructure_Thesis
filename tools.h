#ifndef TOOLS
#define TOOLS

#include <cmath>
#include "vector2f.h"
#include "constants.h"

class Tools
{
public:
    static double distance(const Vector2f& v1, const Vector2f& v2);

    static double randomnum(double min, double max);

    static void nextRandomPosition(Vector2f& curr_pos, pair<Vector2f,Vector2f>& direction,
                                   float direction_factor, double speed, double dt);

    //updates position Node::pos_at_i1 of the node at t_{i+1}
    //in simulation : the node is linearly moved from pos at t_i and pos at t_{i+1}
    static void nextAvailablePosition(Vector2f& pos_at_t, Vector2f& pos_at_t1, float direction_factor, double speed,
                                      float speed_factor, double dt);

    //dot product two vectors
    static double dotProduct(const Vector2f& v1, const Vector2f& v2);

    static float crossProduct2D(const Vector2f& v1, const Vector2f& v2);

    static int sign(float a);

    //checks if a point p lies in middle of edges v1_l.v2_l and v1_r.v2_r
    static bool pointInMiddle(const Vector2f& p, const Vector2f& v1_l, const Vector2f& v2_l, const Vector2f& v1_r, const Vector2f& v2_r);

    static bool intersectionPoint(const Vector2f& v1, const Vector2f& v2, const Vector2f& v3, const Vector2f& v4, Vector2f*& res);

    static double slopeOfLine(const Vector2f& v1, const Vector2f& v2);

    static Vector2f pointOnLineSegmentInGivenDirection(const Vector2f &v0, const Vector2f &v1, float distance);
    static Vector2f rotateAbout(const Vector2f &pivot, double angle_rad, const Vector2f &point);
    static bool lieInCircle(Vector2f& point, Vector2f& center, float radius);
    //pointOnSegment = true if the intersection points must lie on the segment
    static vector<Vector2f> circleIntersectLine(Vector2f &center, float radius, Vector2f &a, Vector2f &b, bool pointOnSegment = true);
    static bool checkIfPointOnSegment(Vector2f &v1, Vector2f &v2, Vector2f &p);
    static bool ifPointInsideConvexHull(const vector<Vector2f> &hull, const Vector2f &point);
    static Vector2f farthestPosInTime(const Vector2f &curr, const Vector2f &p, float speed, float time);
private:
    Tools() = default;
};

#endif // TOOLS

