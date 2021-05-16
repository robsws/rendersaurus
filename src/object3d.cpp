#include "object3d.h"
#include "model.h"
#include "vector.h"
#include "shader.h"
#include "triangle3d.h"
#include "worker_pool.h"
#include <future>

Object3D::Object3D(Model model, Vector position, std::shared_ptr<Shader> shaderPtr) :
    model(model),
    position(position),
    shaderPtr(shaderPtr) {
    scaleVector = Vector(std::vector<float>{1,1,1});
}

void Object3D::render() const {
    // Generate the fragments for this object.
    std::vector<Fragment> fragments;
    // Set the model transformation matrix in the shader.
    // Calculate the matrix to transform a vertex in the model to world space.
    // We will use a 4x4 matrix so that we can use homogeneous coordinates to
    // combine scale, rotation and translation in a single matrix.
    SquareMatrix modelTransform(4, std::vector<float>({
        scaleVector[0], 0,              0,              position[0],
        0,              scaleVector[1], 0,              position[1],
        0,              0,              scaleVector[2], position[2],
        0,              0,              0,              1
    }));
    shaderPtr->setModelTransform(modelTransform);
    // Start tasks to generate fragments for each triangle
	for (Triangle3D triangle : model.getTriangles()) {
		shaderPtr->generateFragments(triangle);
	}
}

void Object3D::translate(const Vector& v) {
    position = position + v;
}

void Object3D::scale(const Vector& v) {
    std::vector<float> newScale = {
        scaleVector[0] * v[0],
        scaleVector[1] * v[1],
        scaleVector[2] * v[2]
    };
    scaleVector = Vector(newScale);
}