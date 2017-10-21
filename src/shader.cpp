#include "shader.h"
#include "vertex.h"
#include "square_matrix.h"
#include "coord.h"
#include "triangle2d.h"

namespace {
    // Interpolate vertex attributes across the face of a triangle for one
    // particular position within the triangle.
    Vertex interpolateVertexAttributes(Triangle3D clipSpaceTriangle, Triangle2D windowSpaceTriangle, Coord position) {
        // Find the barycentric coordinates of the point within the window space
        // triangle.
        Vector barycentricCoords = windowSpaceTriangle.getBarycentricCoords(position);
        // Create a new vertex containing the averaged attributes.
        Vector interpolatedPosition(vector<float>({
            // x coordinate
            barycentricCoords[0] * clipSpaceTriangle.a.position[0] +
            barycentricCoords[1] * clipSpaceTriangle.b.position[0] +
            barycentricCoords[2] * clipSpaceTriangle.c.position[0],
            // y coordinate
            barycentricCoords[0] * clipSpaceTriangle.a.position[1] +
            barycentricCoords[1] * clipSpaceTriangle.b.position[1] +
            barycentricCoords[2] * clipSpaceTriangle.c.position[1],
            // z coordinate
            barycentricCoords[0] * clipSpaceTriangle.a.position[2] +
            barycentricCoords[1] * clipSpaceTriangle.b.position[2] +
            barycentricCoords[2] * clipSpaceTriangle.c.position[2],
            // w coordinate
            1
        }));
        Colour interpolatedColour(
            // red component
            barycentricCoords[0] * clipSpaceTriangle.a.colour.red +
            barycentricCoords[1] * clipSpaceTriangle.b.colour.red +
            barycentricCoords[2] * clipSpaceTriangle.c.colour.red,
            // green component
            barycentricCoords[0] * clipSpaceTriangle.a.colour.green +
            barycentricCoords[1] * clipSpaceTriangle.b.colour.green +
            barycentricCoords[2] * clipSpaceTriangle.c.colour.green,
            // blue component
            barycentricCoords[0] * clipSpaceTriangle.a.colour.blue +
            barycentricCoords[1] * clipSpaceTriangle.b.colour.blue +
            barycentricCoords[2] * clipSpaceTriangle.c.colour.blue
        );
        return Vertex(interpolatedPosition, interpolatedColour);
    }
}

Shader::Shader(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight) {}

vector<Fragment> Shader::generateFragments(const Triangle3D& triangle) const {
    // Transform vertices of triangle to clip space.
    Vertex a = transformVertex(triangle.a);
    Vertex b = transformVertex(triangle.b);
    Vertex c = transformVertex(triangle.c);
    // Transform vertices to window space.
    Coord aDisplayPos = clipSpaceToWindowSpace(a.position);
    Coord bDisplayPos = clipSpaceToWindowSpace(b.position);
    Coord cDisplayPos = clipSpaceToWindowSpace(c.position);
    Triangle2D projectedTriangle(aDisplayPos, bDisplayPos, cDisplayPos);
    // Rasterization (split triangle into digital pixels)
    vector<Coord> pixelLocations = projectedTriangle.rasterize();
    // For each pixel inside triangle, interpolate attributes and calculate the
    // fragment colour.
    vector<Fragment> fragments;
    for (Coord pixel : pixelLocations) {
        Vertex interpolatedAttributes = interpolateVertexAttributes(triangle, projectedTriangle, pixel);
        // Only fragments from inside the screen get rendered.
        if(!(pixel.x < 0 || pixel.x >= windowWidth || pixel.y < 0 || pixel.y >= windowHeight)) {
            fragments.push_back(computeFragmentColour(pixel, interpolatedAttributes));
        }
    }
    return fragments;
}

void Shader::setModelTransform(const SquareMatrix& modelTransform) {
    this->modelTransform = modelTransform;
}

void Shader::setCameraTransform(const SquareMatrix& cameraTransform) {
    this->cameraTransform = cameraTransform;
}

void Shader::setProjectionTransform(const SquareMatrix& projectionTransform) {
    this->projectionTransform = projectionTransform;
}

Coord Shader::clipSpaceToWindowSpace(const Vector& position) const {
    // In clip space, coordinates are in the range -1 to 1.
    // Therefore, we can calculate the pixel positions by expanding this
    // range out to the window width and height.
    // The z coordinate can be ignored.
    // The w coordinate can be used for doing depth interpolation as it contains
    // the original z of the vertex negated.
    Coord windowSpaceCoord(
        ((position[0]+1)/2)*windowWidth,
        ((position[1]+1)/2)*windowHeight
    );
    return windowSpaceCoord;
}