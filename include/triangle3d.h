#pragma once

#include "vertex.h"

class Vector;

class Triangle3D {
    public:
        Triangle3D(Vertex a, Vertex b, Vertex c);
        Vector normal() const;
        Vertex a;
        Vertex b;
        Vertex c;
};