#pragma once

#include "triangle3d.h"

class Model {
  // The Model class is responsible for keeping record of all triangles and
  // their vertices in model space.
  public:
      // Model(string filename);
      Model(vector<Triangle3D> triangles);
      vector<Triangle3D> triangles;
};