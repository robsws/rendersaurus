#include "rendersaurus.h"
#include <iostream>

using namespace std;

Rendersaurus::Rendersaurus(unique_ptr<Display> displayPtr, shared_ptr<Shader> shaderPtr)
    : camera(
        Vector(vector<float>({-1.0f,-1.6f,0.0f,1.0f})),
        Vector(vector<float>({0.0f,0.0f,-1.0f,0.0f})),
        1.0f,
        1000.0f,
        80.0f,
        (float)displayPtr->height / (float)displayPtr->width,
        Projection::PERSPECTIVE
      ),
      scene(this->camera),
      displayPtr(move(displayPtr)),
      shaderPtr(shaderPtr),
      initialised(false)
{}

void Rendersaurus::initialise() {
    // Cannot be called from within constructor due to call on virtual Display functions
    this->shaderPtr->setProjectionTransform(camera.getClipSpaceTransform());
    this->displayPtr->initialise();
}

void Rendersaurus::addObject(const Object3D& object) {
    this->scene.addObject(object);
}

void Rendersaurus::refresh() {
    if (!this->initialised) {
        this->initialise();
    }
    // Update the scene
    scene.update();
    shaderPtr->setCameraTransform(camera.getCameraSpaceTransform());
    // Regenerate the fragments
    vector<Fragment> fragments = scene.render();
    // Update the display
    this->displayPtr->fragmentBufferPtr->blendFragments(fragments);
    this->displayPtr->refresh();
}

Rendersaurus::~Rendersaurus() {
    try {
        displayPtr->finish();
    } catch(...) {
        cerr << "Display threw exception while destroying. Terminating." << endl;
        abort();
    }
}