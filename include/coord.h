#pragma once

#include "vector.h"

class Coord {
    public:
        Coord(int x, int y);
        int x;
        int y;
        Vector getVector() const {
            return Vector(vector<float>({x, y}));
        }
}