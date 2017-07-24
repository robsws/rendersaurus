#pragma once

#include "vertex.h"

class Vector;

class Triangle {
    public:
        Triangle(Vertex a, Vertex b, Vertex c);
        Vector normal() const;
    private:
        Vertex a;
        Vertex b;
        Vertex c;
};