#include "colour.h"

Colour::Colour() :
    red(0.0f), green(0.0f), blue(0.0f) {
}

Colour::Colour(float red, float green, float blue) :
    red(red), green(green), blue(blue) {
}

Colour Colour::operator*(float scalar) const {
    return Colour(scalar * red, scalar * green, scalar * blue);
}

Colour Colour::operator*(const Colour& colour) const {
    return Colour(colour.red * red, colour.green * green, colour.blue * blue);
}

Colour Colour::operator+(const Colour& colour) const {
    return Colour(colour.red + red, colour.green + green, colour.blue + blue);
}

void Colour::set(const Colour& colour) {
    red = colour.red;
    green = colour.green;
    blue = colour.blue;
}