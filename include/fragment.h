#pragma once

#include "colour.h"
#include "coord.h"

class Fragment : public Colour {
    public:
        Fragment();
        Fragment(float red, float green, float blue, Coord position, float depth);
        Fragment& operator=(Fragment fragment);
        Coord getPosition() const;
        float getDepth() const;
        friend void swap(Fragment& first, Fragment& second) noexcept {
            using std::swap;
            Colour& fc = first;
            Colour& sc = second;
            swap(fc, sc);
            swap(first.position, second.position); 
            swap(first.depth, second.depth);
        }
    private:
        Coord position;
        float depth;
};