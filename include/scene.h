#pragma once

#include "object3d.h"
#include "camera.h"

class Scene {
      // The Scene class is responsible for keeping track of all 3D objects in
      // the world and collecting together all the fragments generated by
      // rendering each one individually.
    public:
        // Construct a Scene with the given camera.
        Scene(Camera camera);
        // Render all objects in the scene and collect together the fragments.
        vector<Fragment> render() const;
        // Add an object to the scene to be rendered.
        void addObject(shared_ptr<const Object3D> objectPtr);
    private:
        // List of objects in the scene.
        vector<shared_ptr<const Object3D>> objectPtrs;
        // Camera associated with this scene.
        Camera camera;
};