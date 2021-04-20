#include "basic_shader.h"
#include "vertex.h"
#include "fragment.h"
#include "coord.h"

BasicShader::BasicShader(int width, int height) : Shader(width, height) {}

Vertex BasicShader::transformVertex(const Vertex& vertex) const {
    // Calculate the MVP matrix.
    SquareMatrix MVP = projectionTransform * cameraTransform * modelTransform;
    // Apply it to the vertex position.
    Vector transformedPosition = MVP * vertex.position;
    // Divide through by the w coordinate to normalize to range -1 to 1
    transformedPosition = transformedPosition/transformedPosition[3];
    // Leave the other attributes unchanged.
    return Vertex(transformedPosition, vertex.colour);
}

Fragment BasicShader::computeFragmentColour(const Coord& position, const Vertex& interpolatedVertex) const {
    return Fragment(
        interpolatedVertex.colour.red,
        interpolatedVertex.colour.green,
        interpolatedVertex.colour.blue,
        position,
        interpolatedVertex.position[2]
    );
}