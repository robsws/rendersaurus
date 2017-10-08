#pragma once

#include "vector.h"
#include "square_matrix.h"

class Vertex {
    public:
        Vertex(Vector position);
        Vertex(float x, float y, float z);
        Vector position;
};