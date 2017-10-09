#pragma once

#include "triangle.h"

class Model {
  // The Model class is responsible for keeping record of all triangles and
  // their vertices in model space.
  public:
      Model(string filename);
      Model(vector<Triangle> triangles);
      vector<Triangle> triangles;
}