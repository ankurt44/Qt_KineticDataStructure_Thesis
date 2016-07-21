#include "tools.h"
#include <math.h>


double Tools::distance(const Vector2f& v1, const Vector2f& v2)
{
    return sqrt((v1.x-v2.x) * (v1.x-v2.x)  + (v1.y-v2.y) * (v1.y-v2.y));
}

double Tools::randomnum(double min, double max)
{
    //srand(seed);

    int random =  rand();
    double diff = max - min + 1.0;
    if(max < min)
        cout << "the random function. max = " << max << " min = " << min << endl;
    int r = random % (int) diff;

    return min + r;
}

//Not Used
void Tools::nextRandomPosition(Vector2f& curr_pos, pair<Vector2f,Vector2f>& direction,
                               float direction_factor, double speed, double dt)
{
    double disp = speed * dt;
    double ang;
    if(direction.first == direction.second)
    {
        ang = Tools::randomnum(0, 360);
        cout << "function random - if" << endl;
    }
    else
    {
        ang = Tools::randomnum(0, (direction_factor>360)?360:direction_factor);

        double slope_direction = (direction.first.y - direction.second.y)/(direction.first.x - direction.second.x);
        double ang_xaxis = atan(slope_direction);

        ang = 180 - ang - direction_factor/2; //check by making a drawing of it
        cout << "function random - else" << endl;
    }

    cout << ang << endl;

    double ang_rad = ang * 2 * PI / 360;

    double disp_x_max = disp * (double) cos(ang_rad);
    double disp_y_max = disp * (double) sin(ang_rad);
    double disp_x = Tools::randomnum((disp_x_max<0)?disp_x_max:0, (disp_x_max>0)?disp_x_max:0);
    double disp_y = Tools::randomnum((disp_y_max<0)?disp_y_max:0, (disp_y_max>0)?disp_y_max:0);

    curr_pos.x += disp_x_max;
    curr_pos.y += disp_y_max;
}

void Tools::nextAvailablePosition(Vector2f &pos_at_t, Vector2f &pos_at_t1, float direction_factor, double speed,
                                  float speed_factor, double dt)
{
    double disp = speed * dt;

    disp = Tools::randomnum(0, disp);

    double ang;
    if(pos_at_t == pos_at_t1)
    {
        ang = Tools::randomnum(0,360);
        double ang_rad = ang * 2 * PI / 360;
        double disp_x = disp * (double) cos(ang_rad);
        double disp_y = disp * (double) sin(ang_rad);

        pos_at_t = pos_at_t1;
        pos_at_t1 = pos_at_t + Vector2f(disp_x, disp_y);

        return;
    }
    else
    {
        double away_from_pos_at_t = Tools::distance(pos_at_t, pos_at_t1) + disp;
        Vector2f v_next = Tools::pointOnLineSegmentInGivenDirection(pos_at_t, pos_at_t1, away_from_pos_at_t);

        pos_at_t = pos_at_t1;

        ang = Tools::randomnum(-direction_factor, direction_factor);
        double ang_rad = ang * 2 * PI / 360;

        pos_at_t1 = Tools::rotateAbout(pos_at_t, ang_rad, v_next);

        /*
        ang = Tools::randomnum(-direction_factor, direction_factor);
        double ang_rad = ang * 2 * PI / 360;

        double s = (double) sin(ang_rad);
        double c = (double) cos(ang_rad);

        pos_at_t1 = pos_at_t1 - pos_at_t;

        float xnew = pos_at_t1.x * c - pos_at_t1.y * s;
        float ynew = pos_at_t1.x * s + pos_at_t1.y * c;

        pos_at_t1 = pos_at_t + Vector2f(xnew, ynew);
        */
    }
}

Vector2f Tools::pointOnLineSegmentInGivenDirection(const Vector2f& v0, const Vector2f& v1, float distance)
{
    Vector2f v = v1 - v0;
    v = v/sqrt(v.x*v.x + v.y*v.y);
    v = v0 + (v * distance);
    return v;
}

Vector2f Tools::rotateAbout(const Vector2f& pivot, double angle_rad, const Vector2f& point)
{
    float s = sin(angle_rad);
    float c = cos(angle_rad);

    Vector2f c_pivot = pivot;
    Vector2f p = point;

    p = p-c_pivot;

    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;

    p = Vector2f(xnew, ynew) + c_pivot;

    return p;
}

//dot product of vectors wrt origin
double Tools::dotProduct(const Vector2f& v1, const Vector2f& v2)
{
    return v1.x*v2.x + v1.y+v2.y;
}

float Tools::crossProduct2D(const Vector2f& v1, const Vector2f& v2)
{
    return v1.x*v2.y - v1.y*v2.x;
}

int Tools::sign(float a)
{
    if(a == 0)
        return 0;

    return a/abs(a);
}

//checks if a point p lies in middle of edges v1_l.v2_l and v1_r.v2_r
bool Tools::pointInMiddle(const Vector2f& p, const Vector2f& v1_l, const Vector2f& v2_l, const Vector2f& v1_r, const Vector2f& v2_r)
{
    Vector2f l_1 = v2_l - v1_l;
    Vector2f l_p = p - v1_l;

    Vector2f r_1 = v2_r - v1_r;
    Vector2f r_p = p - v1_r;

    //sign of the acute angle
    float sign_l = crossProduct2D(l_1, l_p);
    float sign_r = crossProduct2D(r_1, r_p);

    //sign_l /= abs(sign_l);
    //sign_r /= abs(sign_r);
    //sign differs => point in middle
    if(sign(sign_l) != sign(sign_r))
        return true;

    return false;
}

bool Tools::lieInCircle(Vector2f& point, Vector2f& center, float radius)
{
    if(Tools::distance(point, center) <= radius)
        return true;

    return false;
}

vector<Vector2f> Tools::circleIntersectLine(Vector2f& center, float radius, Vector2f&  a, Vector2f& b, bool pointOnSegment)
{
    vector<Vector2f> points;
    if(b.x - a.x == 0)
    {
        if(a.x > center.x + radius || a.x < center.x - radius)
        {
            //does not intersect... do nothing
        }
        else
        {
            float y = center.y + sqrt(radius*radius - pow((a.x-center.x),2));
            Vector2f intersect1(a.x, y);
            if(Tools::checkIfPointOnSegment(a,b,intersect1))
                points.push_back(intersect1);

            y = center.y - sqrt(radius*radius - pow((a.x-center.x),2));
            Vector2f intersect2(a.x, y);
            if(Tools::checkIfPointOnSegment(a,b,intersect2))
                points.push_back(intersect2);
        }

        return points;
    }

    //if line is not vertical
    //http://math.stackexchange.com/questions/228841/how-do-i-calculate-the-intersections-of-a-straight-line-and-a-circle

    //from y=mx + c
    float m = (b.y - a.y)/(b.x - a.x);
    float c = a.y - m * a.x;

    float p = center.x, q = center.y;

    float A = m * m + 1;
    float B = 2 * (m * c - m * q - p);
    float C = q * q - radius * radius + p * p - 2 * c * q + c * c;

    //find solutions to Ax^2 + Bx + C = 0
    float D = B * B - 4 * A * C;

    if(D < 0)
    {//line missed circle
        points.clear();
        return points;
    }
    if(D == 0)                      //line either touches (D = 0) or cuts at  two points (D > 0)
    {
        float x = -B / (2 * A);
        float y = m * x + c;
        points.push_back(Vector2f(x, y));
        return points;
    }
    else if(D > 0)                 //line intersects at two points
    {
        float x = (-B + sqrt(D)) / (2 * A);
        float y = m * x + c;
        Vector2f intersect1(x, y);
        if(Tools::checkIfPointOnSegment(a,b,intersect1))
            points.push_back(intersect1);

        x = (-B - sqrt(D)) / (2 * A);
        y = m * x + c;
        Vector2f intersect2(x, y);
        if(Tools::checkIfPointOnSegment(a,b,intersect2))
            points.push_back(intersect2);

        return points;
    }

    return points;
}

//p lies on the segment, i.e. between v1 and v2
bool Tools::checkIfPointOnSegment(Vector2f& v1, Vector2f& v2, Vector2f& p)
{
    float crossp = Tools::crossProduct2D(v2-v1, p-v1);
    if(crossp > EPSILON_CROSS_PRODUCT_ERROR
            && crossp>=-EPSILON_CROSS_PRODUCT_ERROR)
        return false;

    int left_x, right_x, top_y, bottom_y;
    if(v1.x < v2.x)
    {
        left_x = v1.x;
        right_x = v2.x;
    }else
    {
        left_x = v2.x;
        right_x = v1.x;
    }
    if(v1.y < v2.y)
    {
        top_y = v1.y;
        bottom_y = v2.y;
    }else
    {
        top_y = v2.y;
        bottom_y = v1.y;
    }

    if(left_x <= p.x && p.x <= right_x)
        if(top_y <= p.y && p.y <= bottom_y)
            return true;

    return false;

    /*
    //check if p is aligned with v1 and v2
    if(Tools::crossProduct2D(v2-v1, p-v1) != 0) return false;

    double dotp = Tools::dotProduct(v2-v1, p-v1);
    if(dotp < 0)  return false;

    //sqrd length
    double sqrd_len = pow(Tools::distance(v2, v1), 2);
    if(dotp > sqrd_len) return false;

    return true;
    */

}

bool Tools::intersectionPoint(const Vector2f& v1, const Vector2f& v2, const Vector2f& v3, const Vector2f& v4, Vector2f*& res)
{
    res = NULL; //it will be error is res is taken by reference Vector2f& res

    Vector2f r = v2 - v1;
    Vector2f s = v4 - v3;

    float rXs = Tools::crossProduct2D(r, s);
    float qpXr = Tools::crossProduct2D((v3-v1), r);

    if(rXs == 0) //rXs and qpXr are zero => collinear points; rXs is zero and qpXr is non-zero=> parallel
    {
        return false;
    }

    float t = crossProduct2D((v3-v1), s)/rXs;
    float u = crossProduct2D((v3-v1), r)/rXs;

    if(rXs != 0 && (0<=t && t<=1) && (0<=u && u<=1))
    {
        res = new Vector2f(v1 + r * t);

        return true;
    }

    return false;
}

double Tools::slopeOfLine(const Vector2f& v1, const Vector2f& v2)
{
    return ((double)v2.y - (double)v1.y)/((double)v2.x - (double)v1.x);
}
