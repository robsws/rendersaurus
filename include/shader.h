#pragma once

#include "vertex.h"
#include "square_matrix.h"
#include "coord.h"

class Shader {
    public:
        // Construct a shader with given window dimensions for transforming
        // vertices to window space.
        Shader(int windowWidth, int windowHeight);
        // Given a triangle from a model, transform the coordinates into clip space
        // and then rasterize to produce a list of fragments.
        Vector<Fragment> generateFragments(const Triangle& triangle);
        // Set the model matrix to be used to transform vertices from object
        // space to world space.
        void setModelTransform(const SquareMatrix& model_transform);
        // Set the camera matrix to be used to transform vertices from world
        // space to camera space.
        void setCameraTransform(const SquareMatrix& camera_transform);
        // Set the projection transform to be used to transform vertices from
        // camera space to homogeneous clip space.
        void setProjectionTransform(const SquareMatrix& projection_transform);
    private:
        // Transform a vertex and appropriate attributes from
        // object space to clip space.
        virtual Vertex transformVertex(const Vertex& vertex) = 0;
        // Based on interpolated vertex attributes, apply lighting etc. to compute
        // the colour for a particular position.
        virtual Fragment computeFragmentColour(const Coord& position, const Vertex& interpolatedVertex) = 0;
        // Transform vertex positions from clip space to window space
        Coord clipSpaceToWindowSpace(const Vector& position);
        // Transform to be used to transform vertices from object space to world space
        SquareMatrix modelTransform;
        // Transform to be used to transform vertices from world space to camera space
        SquareMatrix cameraTransform;
        // Transform to be used to transform vertices from camera space to clip space
        SquareMatrix projectionTransform;
        // Width of window used to transform vertices from clip space to window space
        int windowWidth;
        // Height of window used to transform vertices form clip space to window space
        int windowHeight;
}