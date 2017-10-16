#include "triangle2d.h"
#include "coord.h"
#include "vector.h"
#include "square_matrix.h"
#include <algorithm>

using namespace std;

namespace {
    bool pointOnSameSide(Coord point1, Coord point2, Coord vertexA, Coord vertexB) {
        Vector aTo1(vector<float>({(float)(point1.x-vertexA.x), (float)(point1.y-vertexA.y), 1}));
        Vector aTo2(vector<float>({(float)(point2.x-vertexA.x), (float)(point2.y-vertexA.y), 1}));
        Vector aToB(vector<float>({(float)(vertexB.x-vertexA.x), (float)(vertexB.y-vertexA.y), 1}));
        Vector cross1(Vector::cross(aToB, aTo1));
        Vector cross2(Vector::cross(aToB, aTo2));
        return Vector::dot(cross1, cross2) >= 0;
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
    int maxY = max(a.y, max(b.y, c.y));
    // Loop through and check if each (x,y) is within the triangle.
    // If it is, it's added to the return list.
    for(int x = minX; x < maxX; ++x) {
        for(int y = minY; y < maxY; ++y) {
            Coord point(x,y);
            if(pointWithinTriangle(point)) {
                pixels.push_back(point);
            }
        }
    }
    return pixels;
}

Vector Triangle2D::getBarycentricCoords(Coord point) const {
    // Easier to work with the coordinates as vectors here.
    Vector vp(point.getVector());
    Vector va(a.getVector());
    Vector vb(b.getVector());
    Vector vc(c.getVector());
    // Find coordinates using linear algebra
    // To find barycentric coordinates, we solve the equation
    // P = aA + bB + cC
    // where P is the point for which we want to find the coords
    // a, b and c are the barycentric coordinates
    // A, B and C are the vertices of the triangle
    // The equation can be rearranged as simultaneous equations to get b and c
    // then the results can be plugged in to the following equation to get a:
    // 1 = a + b + c
    Vector aToP = vp - va;
    Vector aToB = vb - va;
    Vector aToC = vc - va;
    SquareMatrix m(2, vector<float>({
        Vector::dot(aToB, aToB), Vector::dot(aToB, aToC),
        Vector::dot(aToB, aToC), Vector::dot(aToC, aToC)
    }));
    m = m.inverse();
    Vector v(vector<float>({
        Vector::dot(aToP, aToB),
        Vector::dot(aToP, aToC)
    }));
    Vector bc = m*v;
    float a = 1 - bc[0] - bc[1];
    return Vector(vector<float>({a, bc[0], bc[1]}));
}

bool Triangle2D::pointWithinTriangle(Coord point) const {
    return (
        pointOnSameSide(point, c, a, b) &&
        pointOnSameSide(point, a, b, c) &&
        pointOnSameSide(point, b, c, a)
    );
}