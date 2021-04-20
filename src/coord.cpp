#include "coord.h"
#include "vector.h"
#include <vector>

Coord::Coord(int x, int y) :
    x(x), y(y){
}

Vector Coord::getVector() const {
    return Vector(vector<float>({(float)x, (float)y}));
}