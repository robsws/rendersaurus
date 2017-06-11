#pragma once

class Colour {
    public:
        // Methods
        Colour(float red, float green, float blue);
        Colour operator*(float scalar) const;
        Colour operator*(const Colour& colour) const;
        Colour operator+(const Colour& colour) const;
        void set(const Colour& colour);
        // Instance variables
        float red;
        float green;
        float blue;
};