#pragma once

#include "coord.h"
#include <vector>

using namespace std;

class Triangle2D {
    public:
        Coord a;
        Coord b;
        Coord c;
    
        Triangle2D(Coord a, Coord b, Coord c);
        vector<Coord> rasterize() const;
        Vector getBarycentricCoords(Coord point) const;
        bool pointWithinTriangle(Coord point) const;
};