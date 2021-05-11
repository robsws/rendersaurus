#pragma once

#include <vector>
#include <algorithm>
#include "coord.h"

class Vector {
    public:
        // Construct empty vector
        Vector();
        // Construct zero vector of given size
        Vector(int size);
        // Construct vector with given values
        Vector(std::vector<float> values);
        // Copy constructor
        Vector(const Vector& v);
        // From coord
        Vector(const Coord& c);
        // Vector equality
        bool operator==(const Vector& v) const {
            return values == v.values;
        }
        // Vector negation
        Vector operator-() const;
        // Copy assignment operator
        Vector& operator=(Vector v);
        // Vector addition
        Vector& operator+=(const Vector& v);
        // Vector subtraction
        Vector& operator-=(const Vector& v);
        // Multiplication by scalar
        Vector& operator*=(float scalar);
        // Division by scalar
        Vector& operator/=(float scalar);
        // Normalise vector
        Vector normalise();
        // Magnitude
        float magnitude() const;
        // Get number of dimensions of vector
        int dimensions() const;
        // Element access
        float& operator[](unsigned int index);
        float operator[](unsigned int index) const;
        friend void swap(Vector& first, Vector& second) noexcept {
            using std::swap;
            swap(first.values, second.values);
        }
    private:
		template <typename F>
		void applyComponentWiseOperation(F operation);
        std::vector<float> values;
};

// Vector inequality
inline bool operator!=(const Vector& v, const Vector& w) {
    return !v.operator==(w);
}
// Vector addition
inline Vector operator+(Vector v, const Vector& w) {
    v += w;
    return v;
}
// Vector subtraction
inline Vector operator-(Vector v, const Vector& w) {
    v -= w;
    return v;
}
// Multiplication by scalar
inline Vector operator*(Vector v, float f) {
    v *= f;
    return v;
}
inline Vector operator*(float f, Vector v) {
    v *= f;
    return v;
}
// Division by scalar
inline Vector operator/(Vector v, float f) {
    v /= f;
    return v;
}

// Dot product
float dot(const Vector& a, const Vector& b);
// Cross product
Vector cross(const Vector& a, const Vector& b);
// Vector projection
Vector projection(const Vector& a, const Vector& b);