#include "triangle.h"
#include "vertex.h"
#include "vector.h"

Triangle::Triangle(Vertex a, Vertex b, Vertex c) :
    a(a),
    b(b),
    c(c)
{}

Vector Triangle::normal() const {
    Vector ab = b.position - a.position;
    Vector ac = c.position - a.position;
    return Vector::cross(ab, ac);
}