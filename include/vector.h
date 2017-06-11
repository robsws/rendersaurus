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
        Vector(const Vector& vector);
        // Vector negation
        Vector operator-() const;
        // Vector addition
        Vector operator+(const Vector& vector) const;
        // Vector subtraction
        Vector operator-(const Vector& vector) const;
        // Multiplication by scalar
        Vector operator*(float scalar) const;
        // Division by scalar
        Vector operator/(float scalar) const;
        // Multiplication by matrix
        // Vector operator*(const Matrix& matrix);
        // Dot product
        static float dot(const Vector& a, const Vector& b);
        // Cross product
        // static Vector cross(const Vector& a, const Vector& b);
        // Magnitude
        float magnitude() const;
        // Get number of dimensions of vector
        unsigned int dimensions() const;
        // Getter
        float operator[](int index) const;
        // Setter
        void set(int index, float value);
    private:
        Vector applyComponentWiseOperation(auto operation) const;
        vector<float> values;
};