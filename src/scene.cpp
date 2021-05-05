#include "scene.h"
#include "fragment.h"
#include <vector>

Scene::Scene(Camera camera) : camera(camera) {}

std::vector<Fragment> Scene::render() const {
    // Render all objects in the scene and collect together the fragments.
    std::vector<Fragment> fragments;
    for(auto objectPtr : objectPtrs) {
        std::vector<Fragment> objectFragments(objectPtr->render());
        fragments.insert(fragments.end(), objectFragments.begin(), objectFragments.end());
    }
    return fragments;
}

void Scene::addObject(std::shared_ptr<const Object3D> objectPtr) {
    // Add an object to the scene to be rendered.
    objectPtrs.push_back(objectPtr);
}