#pragma once

#include "coord.h"
#include <vector>

class Vector;

class Triangle2D {
    // Represents a triangle on the 2D plane of the screen. Vertices are made up
    // of integer coordinates representing pixel positions on the display.
    public:
        Triangle2D(Coord a, Coord b, Coord c);
        std::vector<Coord> rasterize() const;
        Vector getBarycentricCoords(Coord point) const;
    private:
        bool pointWithinTriangle(Coord point) const;
        Coord a;
        Coord b;
        Coord c;
};