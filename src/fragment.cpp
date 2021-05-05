#include "fragment.h"

Fragment::Fragment() :
    Colour(0,0,20),
    position({0,0}),
    depth(1.0f){
}

Fragment::Fragment(float red, float green, float blue, Coord position, float depth) :
    Colour(red, green, blue),
    position(position),
    depth(depth){
}

Fragment& Fragment::operator=(Fragment fragment) {
    swap(*this, fragment);
    return *this;
}

Coord Fragment::getPosition() const {
    return position;
}

float Fragment::getDepth() const {
    return depth;
}