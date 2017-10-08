#pragma once

#include "colour.h"
#include "coord.h"

class Fragment : public Colour {
    public:
        Fragment(float red, float green, float blue, Coord position, float depth);
    private:
        Coord position;
        float depth;
};