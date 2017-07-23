#pragma once

#include <vector>

using namespace std;

class Vector {
    public:
        // Construct empty vector
        Vector();
        // Construct zero vector of given size
        Vector(int size);
        // Construct vector with given values
        Vector(vector<float> values);
        // Copy constructor
        Vector(const Vector& v);
        // Vector equality
        Vector operator==(const Vector& v) const;
        // Vector negation
        Vector operator-() const;
        // Vector addition
        Vector operator+(const Vector& v) const;
        // Vector subtraction
        Vector operator-(const Vector& v) const;
        // Multiplication by scalar
        Vector operator*(float scalar) const;
        // Division by scalar
        Vector operator/(float scalar) const;
        // Normalise vector
        Vector normalise();
        // Dot product
        static float dot(const Vector& a, const Vector& b);
        // Cross product
        static Vector cross(const Vector& a, const Vector& b);
        // Vector projection
        static Vector projection(const Vector& a, const Vector& b);
        // Magnitude
        float magnitude() const;
        // Get number of dimensions of vector
        int dimensions() const;
        // Element access
        float& operator[](unsigned int index);
        float operator[](unsigned int index) const;
    private:
        Vector applyComponentWiseOperation(auto operation) const;
        vector<float> values;
};

// Commutativity for multiplying by scalar
Vector operator*(float f, const Vector& v);