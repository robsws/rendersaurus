#pragma once

#include "triangle3d.h"

class Model {
  // The Model class is responsible for keeping record of all triangles and
  // their vertices in model space.
  public:
    // Model(string filename);
    Model(std::vector<Triangle3D> triangles);
    std::vector<Triangle3D> getTriangles() const;
  private:
    std::vector<Triangle3D> triangles;
};