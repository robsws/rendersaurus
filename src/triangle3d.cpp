#include "triangle3d.h"
#include "vertex.h"
#include "vector.h"

Vector normal(const Triangle3D& triangle) {
    Vector ab = triangle.b.position - triangle.a.position;
    Vector ac = triangle.c.position - triangle.a.position;
    return cross(ab, ac);
}