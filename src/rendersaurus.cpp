#include "rendersaurus.h"
#include <iostream>
#include <chrono>

Rendersaurus::Rendersaurus(std::unique_ptr<Display> displayPtr, std::shared_ptr<Shader> shaderPtr)
    : camera(
        Vector(vector<float>({-1.0f,-1.6f,0.0f,1.0f})),
        Vector(vector<float>({0.0f,0.0f,-1.0f,0.0f})),
        1.0f,
        1000.0f,
        80.0f,
        (float)displayPtr->getHeight() / (float)displayPtr->getWidth(),
        Projection::PERSPECTIVE
      ),
      scene(this->camera),
      displayPtr(std::move(displayPtr)),
      shaderPtr(shaderPtr),
      initialised(false)
{}

void Rendersaurus::initialise() {
    // Cannot be called from within constructor due to call on virtual Display functions
    this->shaderPtr->setProjectionTransform(camera.getClipSpaceTransform());
    this->displayPtr->initialise();
}

void Rendersaurus::addObject(shared_ptr<const Object3D> objectPtr) {
    this->scene.addObject(objectPtr);
}

int Rendersaurus::refresh() {
    if (!this->initialised) {
        this->initialise();
    }
    auto start = std::chrono::high_resolution_clock::now();
    shaderPtr->setCameraTransform(camera.getCameraSpaceTransform());
    // Regenerate the fragments
    std::vector<Fragment> fragments = scene.render();
    // Update the display
    this->displayPtr->clear();
    this->displayPtr->blend(fragments);
    this->displayPtr->refresh();
    auto stop = std::chrono::high_resolution_clock::now();
    // Calculate FPS
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    if (duration == 0) {
        duration = 1;
    }
    return 1000000000/duration;
}

Rendersaurus::~Rendersaurus() {
    try {
        displayPtr->finish();
    } catch(...) {
        std::cerr << "Display threw exception while destroying. Terminating." << std::endl;
        abort();
    }
}