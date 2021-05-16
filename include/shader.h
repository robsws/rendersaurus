#pragma once

#include "vertex.h"
#include "square_matrix.h"
#include "coord.h"
#include "fragment.h"
#include "triangle3d.h"
#include "worker_pool.h"
#include <vector>

class Shader {
    public:
        // Construct a shader with given window dimensions for transforming
        // vertices to window space.
        Shader(int windowWidth, int windowHeight);
        // Given a triangle from a model, transform the coordinates into clip space
        // and then rasterize to produce a list of fragments. Executed using internal
		// thread pool.
		void generateFragments(const Triangle3D& triangle);
		// Wait for all remaining fragment generation tasks to complete
		// and return the list of all fragments generated. Also clear the list.
		std::vector<Fragment> getAllGeneratedFragments();
        // Set the model matrix to be used to transform vertices from object
        // space to world space.
        void setModelTransform(const SquareMatrix& modelTransform);
        // Set the camera matrix to be used to transform vertices from world
        // space to camera space.
        void setCameraTransform(const SquareMatrix& cameraTransform);
        // Set the projection transform to be used to transform vertices from
        // camera space to homogeneous clip space.
        void setProjectionTransform(const SquareMatrix& projectionTransform);
    protected:
        // Transform a vertex and appropriate attributes from
        // object space to clip space.
        virtual Vertex transformVertex(const Vertex& vertex) const = 0;
        // Based on interpolated vertex attributes, apply lighting etc. to compute
        // the colour for a particular position.
        virtual Fragment computeFragmentColour(const Coord& position, const Vertex& interpolatedVertex) const = 0;
        // Transform vertex positions from clip space to window space
        Coord clipSpaceToWindowSpace(const Vector& position) const;
        // All transforms should be 4x4 for transforming homogeneous coordinates.
        // Transform to be used to transform vertices from object space to world space.
        SquareMatrix modelTransform;
        // Transform to be used to transform vertices from world space to camera space
        SquareMatrix cameraTransform;
        // Transform to be used to transform vertices from camera space to clip space
        SquareMatrix projectionTransform;
        // Width of window used to transform vertices from clip space to window space
        int windowWidth;
        // Height of window used to transform vertices form clip space to window space
        int windowHeight;
	private:
		mutable WorkerPool workerPool;
		// Actual work to generate fragments for a triangle
		void generateFragmentsImpl(const Triangle3D& triangle);
		// Store all the fragments generated across all operations
		std::vector<Fragment> fragments;
		// Thread safe function to save fragments to internal store
		void recordFragments(const vector<Fragment>& fragments);
		std::mutex fragmentsMutex;
		// Keep track of task futures so we know when all are completed
		std::vector<std::future<void>> generateFragmentsFutures;
		std::mutex generateFragmentsFuturesMutex;
};