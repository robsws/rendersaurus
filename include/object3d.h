#pragma once

#include "model.h"
#include "vector.h"
// #include "quaternion.h"
#include "shader.h"
#include "square_matrix.h"
#include <vector>
#include <memory>

using namespace std;

class Object3D {
  // The Object3D class is responsible for keeping record of the current position,
  // rotation and scale of a Model in world space. The vertices are actually
  // transformed in the Shader.
  public:
    // Construct an Object3D with a particular model in the given world space
    // position using the given shader for generating the fragments for the object.
    Object3D(Model model, Vector position, shared_ptr<Shader> shader);
    // Generate the fragments for this object.
    vector<Fragment> render();
    // Translate the object by the given vector.
    void translate(const Vector& v);
    // Rotate the object by the given quaternion.
    // void rotate(Quaternion q);
    // Scale the object by the given vector.
    void scale(const Vector& v);
  private:
    // The model containing the vertex data for the object.
    Model model;
    // The position of the object in world space.
    Vector position;
    // Quaternion rotation;
    Vector scaleVector;
    // The shader used for rendering this object.
    shared_ptr<Shader> shader;
};