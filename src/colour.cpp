#include "colour.h"

Colour::Colour(float r, float g, float b) :
    _red(r), _green(g), _blue(b) {
}

Colour Colour::operator*(float scalar) {
    return Colour(scalar * _red, scalar * _green, scalar * _blue);
}

Colour Colour::operator*(const Colour& colour) {
    return Colour(colour.red() * _red, colour.green() * _green, colour.blue() * _blue);
}

Colour Colour::operator+(const Colour& colour) {
    return Colour(colour.red() + _red, colour.green() + _green, colour.blue() + _blue);
}

float Colour::red() const {
    return _red;
}

float Colour::green() const {
    return _green;
}

float Colour::blue() const {
    return _blue;
}

void Colour::red(float value) {
    _red = value;
}

void Colour::green(float value) {
    _green = value;
}

void Colour::blue(float value) {
    _blue = value;
}

void Colour::set(const Colour& colour) {
    _red = colour.red();
    _green = colour.green();
    _blue = colour.blue();
}