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
        Vector interpolatedPosition(std::vector<float>({
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
            barycentricCoords[0] * clipSpaceTriangle.a.colour.getR() +
            barycentricCoords[1] * clipSpaceTriangle.b.colour.getR() +
            barycentricCoords[2] * clipSpaceTriangle.c.colour.getR(),
            // green component
            barycentricCoords[0] * clipSpaceTriangle.a.colour.getG() +
            barycentricCoords[1] * clipSpaceTriangle.b.colour.getG() +
            barycentricCoords[2] * clipSpaceTriangle.c.colour.getG(),
            // blue component
            barycentricCoords[0] * clipSpaceTriangle.a.colour.getB() +
            barycentricCoords[1] * clipSpaceTriangle.b.colour.getB() +
            barycentricCoords[2] * clipSpaceTriangle.c.colour.getB()
        );
        return {interpolatedPosition, interpolatedColour};
    }
}

Shader::Shader(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
	workerPool(std::thread::hardware_concurrency() - 1){
}

void Shader::generateFragments(const Triangle3D& triangle) {
	std::lock_guard<std::mutex> futureLock(this->generateFragmentsFuturesMutex);
	std::future<void> taskFuture = this->workerPool.addTask(
		[this, triangle]() {
			this->generateFragmentsImpl(triangle);
		}
	);
	this->generateFragmentsFutures.push_back(std::move(taskFuture));
}

void Shader::generateFragmentsImpl(const Triangle3D& triangle) {
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
    std::vector<Coord> pixelLocations = projectedTriangle.rasterize();
    // For each pixel inside triangle, interpolate attributes and calculate the
    // fragment colour.
    std::vector<Fragment> fragments;
    for (Coord pixel : pixelLocations) {
        Vertex interpolatedAttributes = interpolateVertexAttributes(triangle, projectedTriangle, pixel);
        // Only fragments from inside the screen get rendered.
        if(!(pixel.x < 0 || pixel.x >= windowWidth || pixel.y < 0 || pixel.y >= windowHeight)) {
            fragments.push_back(computeFragmentColour(pixel, interpolatedAttributes));
        }
    }
	this->recordFragments(fragments);
}

void Shader::recordFragments(const std::vector<Fragment>& fragments) {
	std::lock_guard<std::mutex> lock(this->fragmentsMutex);
	this->fragments.insert(this->fragments.end(), fragments.begin(), fragments.end());
}

vector<Fragment> Shader::getAllGeneratedFragments() {
	// Make sure all generate tasks are completed
	{
		std::lock_guard<std::mutex> futureLock(this->generateFragmentsFuturesMutex);
		for (auto& future : this->generateFragmentsFutures) {
			future.get();
		}
		this->generateFragmentsFutures.clear();
	}
	// Return all fragments recorded and clear list
	vector<Fragment> fullList;
	{
		std::lock_guard<std::mutex> lock(this->fragmentsMutex);
		fullList = std::move(this->fragments);
		this->fragments.clear();
	}
	return fullList;
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
    return {
        static_cast<int>(((position[0]+1)/2)*windowWidth),
        static_cast<int>(((position[1]+1)/2)*windowHeight)
    };
}