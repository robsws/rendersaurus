#include "vector.h"
#include "square_matrix.h"
#include <assert.h>
#include <cmath>

Vector::Vector() {}

Vector::Vector(int size) :
    values(size, 0) {
}

Vector::Vector(std::vector<float> values) :
    values(values) {
}

Vector::Vector(const Vector& v) :
    values(v.dimensions(), 0) {
    for (int i = 0; i < v.dimensions(); ++i) {
        values[i] = v[i];
    }
}

Vector::Vector(const Coord& c) :
    values(2, 0) {
    values[0] = c.x;
    values[1] = c.y;
}

template <typename F>
void Vector::applyComponentWiseOperation(F operation) {
    using std::swap;
    auto v = Vector(*this);
    for (unsigned int i = 0; i < v.values.size(); ++i) {
        v[i] = operation(i);
    }
    swap(*this, v);
}

Vector& Vector::operator=(Vector v) {
    swap(*this, v);
    return *this;
}

Vector Vector::operator-() const {
    auto negate = [&] (int i) {return -values[i];};
    auto v = Vector(*this);
    v.applyComponentWiseOperation(negate);
    return v;
}

Vector& Vector::operator+=(const Vector& v) {
    assert((int)values.size() == v.dimensions());
    auto add = [&] (int i) {return values[i] + v[i];};
    applyComponentWiseOperation(add);
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    assert((int)values.size() == v.dimensions());
    auto subtract = [&] (int i) {return values[i] - v[i];};
    applyComponentWiseOperation(subtract);
    return *this;
}

Vector& Vector::operator*=(float scalar) {
    auto multiply = [&] (int i) {return values[i] * scalar;};
    applyComponentWiseOperation(multiply);
    return *this;
}

Vector& Vector::operator/=(float scalar) {
    auto divide = [&] (int i) {return values[i] / scalar;};
    applyComponentWiseOperation(divide);
    return *this;
}

Vector Vector::normalise() {
    return (*this)/magnitude();
}

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

float dot(const Vector& a, const Vector& b) {
    assert(a.dimensions() == b.dimensions());
    float result = 0;
    for (int i = 0; i < a.dimensions(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

Vector cross(const Vector& a, const Vector& b) {
    assert(a.dimensions() == 3);
    assert(b.dimensions() == 3);
    // Use matrix transformation to get cross product
    SquareMatrix crossTransform(a.dimensions(), std::vector<float>({
         0.0f, -a[2],  a[1],
         a[2],  0.0f, -a[0],
        -a[1],  a[0],  0.0f
    }));
    return crossTransform * b;
}

Vector projection(const Vector& a, const Vector& b) {
    assert(a.dimensions() == 3);
    assert(b.dimensions() == 3);
    // Use matrix transformation to get projection
    SquareMatrix projectionTransform(a.dimensions(), std::vector<float>({
        b[0]*b[0], b[0]*b[1], b[0]*b[2],
        b[0]*b[1], b[1]*b[1], b[1]*b[2],
        b[0]*b[2], b[1]*b[2], b[2]*b[2]
    }));
    projectionTransform = projectionTransform / pow(b.magnitude(),2);
    return projectionTransform * a;
}