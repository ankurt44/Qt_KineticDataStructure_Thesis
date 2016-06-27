#ifndef VORONOICELL
#define VORONOICELL

#include <vector>

#include "vector2f.h"

class VoronoiCell
{
public:
    vector<Vector2f> left;
    vector<Vector2f> right;

    VoronoiCell()
    {
        left = vector<Vector2f>();
        right = vector<Vector2f>();
    }
    VoronoiCell(const VoronoiCell& cell)
    {
        left = cell.left;
        right = cell.right;
    }
};


#endif // VORONOICELL

