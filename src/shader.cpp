#include "shader.h"
#include "vertex.h"
#include "square_matrix.h"
#include "coord.h"

Shader::Shader(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight) {}

vector<Fragment> Shader::generateFragments(const Triangle& triangle) {
    // Transform vertices of triangle to clip space.
    Vertex a = transformVertex(triangle.a);
    Vertex b = transformVertex(triangle.b);
    Vertex c = transformVertex(triangle.c);
    // Transform vertices to window space.
    Coord aWindowPos = clipSpaceToWindowSpace(a.position);
    Coord bWindowPos = clipSpaceToWindowSpace(b.position);
    Coord cWindowPos = clipSpaceToWindowSpace(c.position);
    // Rasterization (split triangle into digital pixels)
    vector<Coord> pixelLocations = rasterizeTriangle(aWindowPos, bWindowPos, cWindowPos);
    // For each pixel inside triangle, interpolate attributes and calculate the
    // fragment colour.
    vector<Fragment> fragments;
    for (Coord pixel : pixelLocations) {
        Vertex interpolatedAttributes = interpolateVertexAttributes(triangle, pixel, aWindowPos, bWindowPos, cWindowPos);
        fragments.push_back(computeFragmentColour(pixelLocation, interpolatedAttributes));
    }
    return fragments;
}

void Shader::setModelTransform(const SquareMatrix& model_transform) {

}

void Shader::setCameraTransform(const SquareMatrix& camera_transform) {

}

void Shader::setProjectionTransform(const SquareMatrix& projection_transform) {

}

Coord Shader::clipSpaceToWindowSpace(const Vector& position) {

}