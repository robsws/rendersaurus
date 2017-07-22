#include "vector.h"

#include <assert.h>
#include <cmath>
#include <iostream>

Vector::Vector() {
    // Construct empty vector
    values = vector<float>();
}

Vector::Vector(int size) {
    // Construct zero vector of given size
    values = vector<float>(size, 0);
}

Vector::Vector(vector<float> values) {
    // Construct vector with given values
    this->values = vector<float>(values);
}

Vector::Vector(const Vector& v) {
    values = vector<float>(v.dimensions(), 0);
    for (int i = 0; i < v.dimensions(); ++i) {
        values[i] = v[i];
    }
}

Vector Vector::operator==(const Vector& v) const {
    if(dimensions() != v.dimensions()) {
        return false;
    }
    bool equal = true;
    for(unsigned int i = 0; i < values.size(); ++i) {
        equal = equal && values[i] == v[i];
    }
    return equal;
}

Vector Vector::applyComponentWiseOperation(auto operation) const {
    Vector v = Vector(*this);
    for (unsigned int i = 0; i < values.size(); ++i) {
        v[i] = operation(i);
    }
    return v;
}

Vector Vector::operator-() const { 
    auto negate = [&] (int i) {return -values[i];};
    return applyComponentWiseOperation(negate);
}

Vector Vector::operator+(const Vector& v) const {
    assert((int)values.size() == v.dimensions());
    auto add = [&] (int i) {return values[i] + v[i];};
    return applyComponentWiseOperation(add);
}

Vector Vector::operator-(const Vector& v) const {
    assert((int)values.size() == v.dimensions());
    auto subtract = [&] (int i) {return values[i] - v[i];};
    return applyComponentWiseOperation(subtract);
}

Vector Vector::operator*(float scalar) const {
    auto multiply = [&] (int i) {return values[i] * scalar;};
    return applyComponentWiseOperation(multiply);
}

Vector Vector::operator/(float scalar) const {
    auto divide = [&] (int i) {return values[i] / scalar;};
    return applyComponentWiseOperation(divide);
}

Vector Vector::normalise() {
    return (*this)/magnitude();
}

float Vector::dot(const Vector& a, const Vector& b) {
    assert(a.dimensions() == b.dimensions());
    float result = 0;
    for (int i = 0; i < a.dimensions(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// Vector Vector::cross(const Vector& a, const Vector& b) {
//     // Cross product for orthogonality only makes sense on 3D vector
//     assert(a.dimensions() == 3);
//     assert(b.dimensions() == 3);
//     // Use matrix transformation to get cross product
// }

float Vector::magnitude() const {
    float sumOfSquares = 0;
    for (unsigned int i = 0; i < values.size(); ++i) {
        sumOfSquares += values[i]*values[i];
    }
    return sqrt(sumOfSquares);
}

int Vector::dimensions() const {
    // Get number of dimensions of vector
    return (int)values.size();
}

float& Vector::operator[](unsigned int index) {
    // Element access
    assert(index < values.size());
    return values[index];
}

float Vector::operator[](unsigned int index) const {
    // Element access
    assert(index < values.size());
    return values[index];
}

// Commutativity for multiplying by scalar
Vector operator*(float f, const Vector& v) {
    return v*f;
}