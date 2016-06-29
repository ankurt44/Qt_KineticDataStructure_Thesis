#ifndef NODE
#define NODE

#include <cmath>
#include <map>

#include "vector2f.h"
#include "voronoicell.h"
#include "tools.h"
#include "alg.h"

/*
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};
*/

class Node
{
public:
    const static float C = 1;
    const static float FACTOR = 2;

    Vector2f pos;
    vector<Node*> children;
    VoronoiCell cell;
    float velocity;


    Node() = default;

    Node(const Vector2f& _pos, float _velocity = 0.0f, float _range = 0.0f);

    Node(const Node& node);

    float getRange();

    const Node* getFarChild();

    double getEnergy();

    void addInterpolation(ALG_VARIANT _alg, vector<pair<float, float> > _i);

    //ToDo: linear interpolation. can allow someone to pass interpolation function pointer as argument
    //                                  (default could be a function that does linear interpolation)
    float getRangeAt(ALG_VARIANT _alg, float _time);

private:
    //force to call getRange, and update range as per farthest child
    float range;

    //variant to <time, range>
    map<ALG_VARIANT, vector<pair<float, float> > > interpolation;

};

#endif // NODE

