#pragma once

#include <algorithm>

class Colour {
    public:
        // Methods
        Colour();
        virtual ~Colour() = default;
        Colour(float red, float green, float blue);
        Colour& operator=(Colour colour);
        Colour& operator*=(const Colour& colour);
        Colour& operator*=(float scalar);
        Colour& operator+=(const Colour& colour);
        float getR() const;
        float getG() const;
        float getB() const;
        friend void swap(Colour& first, Colour& second) noexcept {
            using std::swap;
            swap(first.r, second.r); 
            swap(first.g, second.g);
            swap(first.b, second.b);
        }
    private:
        float r;
        float g;
        float b;
};

inline Colour operator*(Colour colour, float scalar) {
    colour *= scalar;
    return colour;
}

inline Colour operator*(Colour colour, const Colour& colour2) {
    colour *= colour2;
    return colour;
}

inline Colour operator+(Colour colour, const Colour& colour2) {
    colour += colour2;
    return colour;
}