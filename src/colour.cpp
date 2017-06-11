#include "colour.h"

Colour::Colour(float red, float green, float blue) :
    red(red), green(green), blue(blue) {
}

Colour Colour::operator*(float scalar) {
    return Colour(scalar * red, scalar * green, scalar * blue);
}

Colour Colour::operator*(const Colour& colour) {
    return Colour(colour.red * red, colour.green * green, colour.blue * blue);
}

Colour Colour::operator+(const Colour& colour) {
    return Colour(colour.red + red, colour.green + green, colour.blue + blue);
}

void Colour::set(const Colour& colour) {
    red = colour.red;
    green = colour.green;
    blue = colour.blue;
}