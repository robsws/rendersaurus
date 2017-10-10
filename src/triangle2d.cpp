#include "triangle2d.h"
#include "coord.h"
#include "vector.h"
#include <algorithm>

using namespace std;

namespace {
    bool pointOnSameSide(Coord point1, Coord point2, Coord vertexA, Coord vertexB) {
        Vector aTo1(vector<float>({point1.x-vertexA.x, point1.y-vertexA.y, 1}));
        Vector aTo2(vector<float>({point2.x-vertexA.x, point2.y-vertexA.y, 1}));
        Vector aToB(vector<float>({vertexB.x-vertexA.x, vertexB.y-vertexA.y, 1}));
        Vector cross1(Vector::cross(aToB, aTo1));
        Vector cross2(Vector::cross(aToB, aTo2));
        return Vector::dot(cross1, cross2) >= 0);
    }
}

Triangle2D::Triangle2D(Coord a, Coord b, Coord c) :
    a(a),
    b(b),
    c(c)
{}

vector<Coord> Triangle2D::rasterize() const {
    // Start at min (x,y) for triangle vertices and end at max (x,y).
    vector<Coord> pixels;
    int minX = min(a.x, min(b.x, c.x));
    int minY = min(a.y, min(b.y, c.y));
    int maxX = max(a.x, max(b.x, c.x));
    int maxY = max(a.x, max(b.x, c.x));
    // Loop through and check if each (x,y) is within the triangle.
    // If it is, it's added to the return list.
    for(int x = minX; x < maxX; ++x) {
        for(int y = minY; y < minY; ++y) {
            Coord point(x,y);
            if(pointWithinTriangle(point)) {
                pixels.push_back(point);
            }
        }
    }
    return pixels;
}

bool Triangle2D::pointWithinTriangle(Coord point) {
    return (
        pointOnSameSide(point, c, a, b) &&
        pointOnSameSide(point, a, b, c) &&
        pointOnSameSide(point, b, c, a)
    );
}