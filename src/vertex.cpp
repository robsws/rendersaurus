#include "vertex.h"
#include "vector.h"

Vertex::Vertex(Vector position) :
    position(position)
{}

Vertex::Vertex(float a, float b, float c) {
    position = Vector(vector<float>({a, b, c}));
}