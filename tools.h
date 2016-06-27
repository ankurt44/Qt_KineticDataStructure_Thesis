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

    static void nextRandomPosition(Vector2f& curr_pos, double speed, double dt);

    //dot product v1v2.v2v3
    static double dotProduct(const Vector2f& v1, const Vector2f& v2, const Vector2f& v3);

    static float crossProduct2D(const Vector2f& v1, const Vector2f& v2);

    static int sign(float a);

    //checks if a point p lies in middle of edges v1_l.v2_l and v1_r.v2_r
    static bool pointInMiddle(const Vector2f& p, const Vector2f& v1_l, const Vector2f& v2_l, const Vector2f& v1_r, const Vector2f& v2_r);

    static bool intersectionPoint(const Vector2f& v1, const Vector2f& v2, const Vector2f& v3, const Vector2f& v4, Vector2f*& res);

    static double slopeOfLine(const Vector2f& v1, const Vector2f& v2);

private:
    Tools() = default;
};

#endif // TOOLS

