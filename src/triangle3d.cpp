#include "triangle3d.h"
#include "vertex.h"
#include "vector.h"

Triangle3D::Triangle3D(Vertex a, Vertex b, Vertex c) :
    a(a),
    b(b),
    c(c)
{}

Vector Triangle3D::normal() const {
    Vector ab = b.position - a.position;
    Vector ac = c.position - a.position;
    return Vector::cross(ab, ac);
}