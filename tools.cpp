#include "tools.h"


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
        cout << "shit happened in the random function. max = " << max << " min = " << min << endl;
    int r = random % (int) diff;

    return min + r;
}

void Tools::nextRandomPosition(Vector2f& curr_pos, double speed, double dt)
{
    double disp = speed * dt;
    double ang = Tools::randomnum(0, 360);
    double ang_rad = ang * 2 * PI / 360;

    double disp_x_max = disp * (double) cos(ang_rad);
    double disp_y_max = disp * (double) sin(ang_rad);
    double disp_x = Tools::randomnum((disp_x_max<0)?disp_x_max:0, (disp_x_max>0)?disp_x_max:0);
    double disp_y = Tools::randomnum((disp_y_max<0)?disp_y_max:0, (disp_y_max>0)?disp_y_max:0);

    curr_pos.x += disp_x;
    curr_pos.y += disp_y;
    //curr_pos.x += disp * (double) cos(ang_rad);
    //curr_pos.y += disp * (double) sin(ang_rad);
}

//dot product v1v2.v2v3
double Tools::dotProduct(const Vector2f& v1, const Vector2f& v2, const Vector2f& v3)
{
    return 0.0;
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
