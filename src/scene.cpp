#include "scene.h"
#include "fragment.h"
#include <vector>

Scene::Scene(Camera camera) : camera(camera) {}

void Scene::render() const {
    // Render all objects in the scene and collect together the fragments.
    for(auto objectPtr : objectPtrs) {
        objectPtr->render();
    }
}

void Scene::addObject(std::shared_ptr<const Object3D> objectPtr) {
    // Add an object to the scene to be rendered.
    objectPtrs.push_back(objectPtr);
}