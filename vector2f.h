#ifndef VECTOR2F
#define VECTOR2F

#include <iostream>

using namespace std;

class Vector2f
{
public:
    float x, y;

    Vector2f() = default;

    Vector2f(float _x, float _y) : x(_x), y(_y) {}

    Vector2f(const Vector2f& v) : x(v.x), y(v.y) {}

    Vector2f& operator=(const Vector2f& v)
    {
        x = v.x;
        y = v.y;

        return *this;
    }

    bool operator==(const Vector2f& v) {return (x==v.x && y==v.y);}

    friend bool operator>(const Vector2f& v1, const Vector2f& v2)
    {
        return ((v1.y == v2.y) ? (v1.x < v2.x) : (v1.y > v2.y));
    }

    friend bool operator<(const Vector2f& v1, const Vector2f& v2)
    {
        return ((v1.y == v2.y) ? (v1.x > v2.x) : (v1.y < v2.y));
    }

    friend Vector2f& operator+(const Vector2f& v1, const Vector2f& v2)
    {
        Vector2f* res = new Vector2f(v1.x+v2.x, v1.y+v2.y);
        return *res;
    }

    friend Vector2f& operator+(const Vector2f& v1, float scalar)
    {
        Vector2f* res = new Vector2f(v1.x+scalar, v1.y+scalar);
        return *res;
    }

    friend Vector2f& operator-(const Vector2f& v1, const Vector2f& v2)
    {
        Vector2f* res = new Vector2f(v1.x-v2.x, v1.y-v2.y);
        return *res;
    }

    friend Vector2f& operator-(const Vector2f& v1, float scalar)
    {
        Vector2f* res = new Vector2f(v1.x-scalar, v1.y-scalar);
        return *res;
    }

    friend Vector2f& operator*(const Vector2f& v1, float scalar)
    {
        Vector2f* res = new Vector2f(v1.x*scalar, v1.y*scalar);
        return *res;
    }

    friend Vector2f& operator/(const Vector2f& v1, float scalar)
    {
        Vector2f* res = new Vector2f(v1.x/scalar, v1.y/scalar);
        return *res;
    }

    friend ostream& operator<<(ostream& out, Vector2f& v)
    {
        return out << v.x << ", " << v.y;
    }

};


struct sort_decreasing
{
    bool operator()(const Vector2f& v1, const Vector2f& v2)
    {
        return ((v1.y == v2.y) ? (v1.x > v2.x) : (v1.y > v2.y));
    }
};

#endif // VECTOR2F

