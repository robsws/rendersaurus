#include "scene.h"
#include "fragment.h"
#include <vector>

Scene::Scene(Camera camera) : camera(camera) {}

vector<Fragment> Scene::render() const {
    // Render all objects in the scene and collect together the fragments.
    vector<Fragment> fragments;
    for(Object3D object : objects) {
        fragments.append(object.render());
    }
}

void Scene::addObject(const Object3D& object) {
    // Add an object to the scene to be rendered.
    objects.push_back(object);
}

void Scene::update() {
    // Update positions of objects in the scene.
}