#pragma once

#include "vertex.h"
#include <vector>

using namespace std;

class Triangle3D {
    public:
        Vertex a;
        Vertex b;
        Vertex c;
        
        Triangle3D(Vertex a, Vertex b, Vertex c);
        Vector normal() const;
};