#include "object3d.h"
#include "model.h"
#include "vector.h"
#include "shader.h"
#include "triangle3d.h"

Object3D::Object3D(Model model, Vector position, shared_ptr<Shader> shader) :
    model(model),
    position(position),
    shader(shader) {}

vector<Fragment> Object3D::render() const {
    // Generate the fragments for this object.
    vector<Fragment> fragments;
    // Set the model transformation matrix in the shader.
    // Calculate the matrix to transform a vertex in the model to world space.
    // We will use a 4x4 matrix so that we can use homogeneous coordinates to
    // combine scale, rotation and translation in a single matrix.
    SquareMatrix modelTransform(4, vector<float>({
        scaleVector[0], 0,              0,              position[0],
        0,              scaleVector[1], 0,              position[1],
        0,              0,              scaleVector[2], position[2],
        0,              0,              0,              1
    }));
    shader->setModelTransform(modelTransform);
    // Pass each triangle in the model through the shader and add the fragments
    // generated to the list.
    for (Triangle3D triangle : model.triangles) {
        vector<Fragment> triangleFragments = shader->generateFragments(triangle);
        fragments.insert(fragments.end(), triangleFragments.begin(), triangleFragments.end());
    }
    return fragments;
}

void Object3D::translate(const Vector& v) {
    position = position + v;
}

void Object3D::scale(const Vector& v) {
    vector<float> newScale = {
        scaleVector[0] * v[0],
        scaleVector[1] * v[1],
        scaleVector[2] * v[2]
    };
    scaleVector = newScale;
}