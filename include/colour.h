#pragma once

class Colour {
    public:
        // Methods
        Colour(float red, float green, float blue);
        Colour operator*(float scalar);
        Colour operator*(const Colour& colour);
        Colour operator+(const Colour& colour);
        void set(const Colour& colour);
        // Instance variables
        float red;
        float green;
        float blue;
};