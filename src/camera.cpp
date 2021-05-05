#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#include "camera.h"
#include "square_matrix.h"
#include "vector.h"
#include <cmath>

Camera::Camera(Vector position, Vector direction, float nearClipDistance, float farClipDistance, float fovAngle, float aspectRatio, Projection projection) :
    position(position),
    direction(direction),
    nearClipDistance(nearClipDistance),
    farClipDistance(farClipDistance),
    fovAngle(fovAngle),
    aspectRatio(aspectRatio),
    projection(projection) {
}

SquareMatrix Camera::getCameraSpaceTransform() const {
    // To get to camera space we need to perform a translation in the opposite
    // direction from the direction the camera is away from the origin.
    // TODO - encorporate direction (rotation)
    SquareMatrix cameraTransform(4, std::vector<float>({
        1,0,0,position[0],
        0,1,0,position[1],
        0,0,1,position[2],
        0,0,0,1
    }));
    return cameraTransform;
}

SquareMatrix Camera::getClipSpaceTransform() const {
    // Generate either an orthographic or perspective projection matrix
    // TODO - add orthographic
    float projectionPlaneDistance = 1/tan(fovAngle*(M_PI/180.0f)/2);
    // Calculate edges of near clip plane
    float n = nearClipDistance;
    float f = farClipDistance;
    float l = -nearClipDistance/projectionPlaneDistance;
    float r = nearClipDistance/projectionPlaneDistance;
    float t = aspectRatio*nearClipDistance/projectionPlaneDistance;
    float b = -aspectRatio*nearClipDistance/projectionPlaneDistance;
    // Generate the matrix
    SquareMatrix clipTransform(4, std::vector<float>({
        (2 * n) / (r - l), 0,                 (r + l) / (r - l),  0,
        0,                 (2 * n) / (t - b), (t + b) / (t - b),  0,
        0,                 0,                -(f + n) / (f - n),  (-2*n*f)/(f-n),
        0,                 0,                -1,                  0
    }));
    return clipTransform;
}