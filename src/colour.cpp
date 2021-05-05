#include "colour.h"

Colour::Colour() :
    r(0.0f), g(0.0f), b(0.0f) {
}

Colour::Colour(float red, float green, float blue) :
    r(red), g(green), b(blue) {
}

Colour& Colour::operator=(Colour colour) {
    swap(*this, colour);
    return *this;
}

Colour& Colour::operator*=(const Colour& colour) {
    r *= colour.r; g *= colour.g; b *= colour.b;
    return *this;
}

Colour& Colour::operator*=(float scalar) {
    r *= scalar; g *= scalar; b *= scalar;
    return *this;
}

Colour& Colour::operator+=(const Colour& colour) {
    r += colour.r; g += colour.g; b += colour.b;
    return *this;
}

float Colour::getR() const {
    return r;
}

float Colour::getG() const {
    return g;
}

float Colour::getB() const {
    return b;
}