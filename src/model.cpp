#include "model.h"
#include <vector>

Model::Model(std::vector<Triangle3D> triangles):
    triangles(triangles) {
}

std::vector<Triangle3D> Model::getTriangles() const {
    return triangles;
}