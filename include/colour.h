#pragma once

class Colour {
    public:
        Colour(float r, float g, float b);
        Colour operator*(float scalar);
        Colour operator*(const Colour& colour);
        Colour operator+(const Colour& colour);
        // Getters
        float red() const;
        float green() const;
        float blue() const;
        // Setters
        void red(float value);
        void green(float value);
        void blue(float value);
        void set(const Colour& colour);
    private:
        float _red;
        float _green;
        float _blue;
};