#pragma once

#include "colour.h"
#include "coord.h"

class Fragment : public Colour {
    public:
        Fragment();
        Fragment(float red, float green, float blue, Coord position, float depth);
        Coord position;
        float depth;
};