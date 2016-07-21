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
    Node() = default;

    Node(const Vector2f& _pos_at_t, const Vector2f& _pos_at_t1, float _velocity = 0.0f, float _range = 0.0f);

    Node(const Node& node);

    //float getRange();

    const Node* getFarChild();

    void updateInitialRange(ALG_VARIANT _alg, float _time);

    double getPower(ALG_VARIANT _alg) const;

    void addInterpolation(ALG_VARIANT _alg, vector<pair<float, float> > _i);

    //ToDo: linear interpolation. can allow someone to pass interpolation function pointer as argument
    //                                  (default could be a function that does linear interpolation)
    float getRangeAt(ALG_VARIANT _alg, float _time);

    void updateRangeAt(ALG_VARIANT _alg, float _total_time, float _time); //updates time and range;
                                                                          //_time is used to get range within interval period

    float currentRange(ALG_VARIANT _alg) const;

    vector<pair<float, float> > rangeDataVector(ALG_VARIANT _alg);

    const static float C = 1;
    const static float FACTOR = 2;

    Vector2f pos;
    Vector2f pos_at_ti;
    Vector2f pos_at_ti1;
    vector<Node*> children;
    VoronoiCell cell;
    float velocity;
    int order;

private:
    //force to call getRange, and update range as per farthest child
    //float range;

    map<ALG_VARIANT, vector<pair<float, float> > > alg_range;

    //variant to <time, range>
    map<ALG_VARIANT, vector<pair<float, float> > > interpolation;


};

#endif // NODE

