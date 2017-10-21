#include "xterm_display.h"
#include "camera.h"
#include "scene.h"
#include "basic_shader.h"
#include "triangle3d.h"
#include "object3d.h"
#include "fragment_buffer.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <width> <height>" << endl;
        return EXIT_FAILURE;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    // Set up the world, camera and shader
    Camera camera(
        Vector(vector<float>({0.0f,0.0f,0.0f,1.0f})),
        Vector(vector<float>({0.0f,0.0f,-1.0f,0.0f})),
        1.0f,
        1000.0f,
        90.0f,
        (float)height / (float)width,
        Projection::PERSPECTIVE);
    Scene scene(camera);
    shared_ptr<Shader> shaderPtr(new BasicShader(width, height));
    shaderPtr->setProjectionTransform(camera.getClipSpaceTransform());

    // Set up the objects in the world
    Vertex a(Vector(vector<float>({1.0f,1.0f,1.0f,1.0f})), Colour(255,0,0));
    Vertex b(Vector(vector<float>({2.0f,1.0f,1.0f,1.0f})), Colour(0,255,0));
    Vertex c(Vector(vector<float>({1.0f,2.0f,1.0f,1.0f})), Colour(0,0,255));
    Triangle3D triangle(a, b, c);
    Model model(vector<Triangle3D>({triangle}));
    Object3D obj(model, Vector(vector<float>({0.0f,0.0f,2.0f,1.0f})), shaderPtr);
    scene.addObject(obj);

    // Initialise the display
    shared_ptr<FragmentBuffer> fragmentBufferPtr(new FragmentBuffer(width, height));
    XtermDisplay display(width, height, fragmentBufferPtr);
    display.initialise();

    for(int i = 0; i < 100; ++i) {
        // Update the scene
        scene.update();
        shaderPtr->setCameraTransform(camera.getCameraSpaceTransform());
        // Regenerate the fragments
        vector<Fragment> fragments = scene.render();
        // Update the display
        fragmentBufferPtr->blendFragments(fragments);
        display.refresh();
    }
    display.finish();

    return EXIT_SUCCESS;
}