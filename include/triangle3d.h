#pragma once

#include "vertex.h"
#include "vector.h"

struct Triangle3D {
    Vertex a;
    Vertex b;
    Vertex c;
};

Vector normal(const Triangle3D& triangle);