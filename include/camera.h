#pragma once

#include "vector.h"

enum Projection {
  PROJECTION_PERSPECTIVE,
  PROJECTION_ORTHO
};

class Camera {
    public:
        // Construct a camera in the given position facing the given direction
        // with a view frustum of the given dimensions with the given type of
        // projection.
        Camera(
          Vector position,
          Vector direction,
          float nearClipDistance,
          float farClipDistance,
          float fovAngle,
          Projection projection
          );
        // Generate the view matrix to transform vertices based on the camera attributes.
        SquareMatrix getCameraSpaceTransform() const;
        // Generate the projection matrix based on the type of projection selected
        // and dimensions of the view frustum.
        SquareMatrix getClipSpaceTransform() const;
    private:
        // Where the camera exists in world space.
        Vector position;
        // Which direction the camera points in in world space.
        Vector direction;
        // The distance from the camera to the near plane of the view frustum.
        float nearClipDistance,
        // The distance from the camera to the far plane of the view frustum.
        float farClipDistance,
        // The horizontal field of view angle.
        float fovAngle,
        // The type of projection to use.
        Projection projection;
}