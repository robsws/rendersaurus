#pragma once

#include "vector.h"
#include "colour.h"
#include "square_matrix.h"

class Vertex {
    public:
        Vertex(Vector position);
        Vertex(float x, float y, float z);
        Vertex(Vector position, Colour colour)
        Vector position;
        Colour colour;
};