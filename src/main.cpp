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

Object3D createCube(Vector position, shared_ptr<Shader> shaderPtr) {
    // 8 vertices in total, some can be reused
    // Vertex a(Vector(vector<float>({-0.5f,-0.5f,-0.5f,1.0f})), Colour(255,0,0));
    // Vertex b(Vector(vector<float>({0.5f,-0.5f,-0.5f,1.0f})), Colour(255,0,0));
    // Vertex c(Vector(vector<float>({-0.5f,0.5f,-0.5f,1.0f})), Colour(255,0,0));
    // Vertex d(Vector(vector<float>({0.5f,0.5f,-0.5f,1.0f})), Colour(255,0,0));
    // Vertex e(Vector(vector<float>({-0.5f,-0.5f,0.5f,1.0f})), Colour(255,0,0));
    // Vertex f(Vector(vector<float>({0.5f,-0.5f,0.5f,1.0f})), Colour(255,0,0));
    // Vertex g(Vector(vector<float>({-0.5f,0.5f,0.5f,1.0f})), Colour(255,0,0));
    // Vertex h(Vector(vector<float>({0.5f,0.5f,0.5f,1.0f})), Colour(255,0,0));
    // each face with it's own vertices for debugging
    Vertex f1a(Vector(vector<float>({-0.5f,-0.5f,-0.5f,1.0f})), Colour(255,0,0));
    Vertex f1b(Vector(vector<float>({0.5f,-0.5f,-0.5f,1.0f})), Colour(255,0,0));
    Vertex f1c(Vector(vector<float>({-0.5f,0.5f,-0.5f,1.0f})), Colour(255,0,0));
    Vertex f1d(Vector(vector<float>({0.5f,0.5f,-0.5f,1.0f})), Colour(255,0,0));
    Vertex f2a(Vector(vector<float>({-0.5f,0.5f,-0.5f,1.0f})), Colour(255,255,0));
    Vertex f2b(Vector(vector<float>({-0.5f,0.5f,0.5f,1.0f})), Colour(255,255,0));
    Vertex f2c(Vector(vector<float>({0.5f,0.5f,-0.5f,1.0f})), Colour(255,255,0));
    Vertex f2d(Vector(vector<float>({0.5f,0.5f,0.5f,1.0f})), Colour(255,255,0));
    Vertex f3a(Vector(vector<float>({0.5f,-0.5f,-0.5f,1.0f})), Colour(0,255,0));
    Vertex f3b(Vector(vector<float>({0.5f,-0.5f,0.5f,1.0f})), Colour(0,255,0));
    Vertex f3c(Vector(vector<float>({0.5f,0.5f,-0.5f,1.0f})), Colour(0,255,0));
    Vertex f3d(Vector(vector<float>({0.5f,0.5f,0.5f,1.0f})), Colour(0,255,0));
    Vertex f4a(Vector(vector<float>({-0.5f,-0.5f,-0.5f,1.0f})), Colour(0,0,255));
    Vertex f4b(Vector(vector<float>({-0.5f,-0.5f,0.5f,1.0f})), Colour(0,0,255));
    Vertex f4c(Vector(vector<float>({-0.5f,0.5f,-0.5f,1.0f})), Colour(0,0,255));
    Vertex f4d(Vector(vector<float>({-0.5f,0.5f,0.5f,1.0f})), Colour(0,0,255));
    Vertex f5a(Vector(vector<float>({-0.5f,-0.5f,-0.5f,1.0f})), Colour(255,0,255));
    Vertex f5b(Vector(vector<float>({0.5f,-0.5f,-0.5f,1.0f})), Colour(255,0,255));
    Vertex f5c(Vector(vector<float>({-0.5f,-0.5f,0.5f,1.0f})), Colour(255,0,255));
    Vertex f5d(Vector(vector<float>({0.5f,-0.5f,0.5f,1.0f})), Colour(255,0,255));
    Vertex f6a(Vector(vector<float>({-0.5f,-0.5f,0.5f,1.0f})), Colour(255,255,255));
    Vertex f6b(Vector(vector<float>({0.5f,-0.5f,0.5f,1.0f})), Colour(255,255,255));
    Vertex f6c(Vector(vector<float>({-0.5f,0.5f,0.5f,1.0f})), Colour(255,255,255));
    Vertex f6d(Vector(vector<float>({0.5f,0.5f,0.5f,1.0f})), Colour(255,255,255));
    // create triangles from the vertices
    // 6 faces x 2 triangles per face
    vector<Triangle3D> triangles;
    triangles.push_back(Triangle3D(f1a, f1b, f1c));
    triangles.push_back(Triangle3D(f1b, f1c, f1d));
    triangles.push_back(Triangle3D(f2a, f2b, f2c));
    triangles.push_back(Triangle3D(f2b, f2c, f2d));
    triangles.push_back(Triangle3D(f3a, f3b, f3c));
    triangles.push_back(Triangle3D(f3b, f3c, f3d));
    triangles.push_back(Triangle3D(f4a, f4b, f4c));
    triangles.push_back(Triangle3D(f4b, f4c, f4d));
    triangles.push_back(Triangle3D(f5a, f5b, f5c));
    triangles.push_back(Triangle3D(f5b, f5c, f5d));
    triangles.push_back(Triangle3D(f6a, f6b, f6c));
    triangles.push_back(Triangle3D(f6b, f6c, f6d));
    // triangles.push_back(Triangle3D(b, d, f));
    // triangles.push_back(Triangle3D(f, d, h));
    // triangles.push_back(Triangle3D(a, c, e));
    // triangles.push_back(Triangle3D(e, c, g));
    // triangles.push_back(Triangle3D(a, e, b));
    // triangles.push_back(Triangle3D(b, e, f));
    // triangles.push_back(Triangle3D(c, g, d));
    // triangles.push_back(Triangle3D(d, g, h));
    // triangles.push_back(Triangle3D(e, g, f));
    // triangles.push_back(Triangle3D(f, g, h));
    // Combine into the object3D
    Model model(triangles);
    return Object3D(model, position, shaderPtr);
}

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
        Vector(vector<float>({-1.0f,-1.6f,0.0f,1.0f})),
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
    // Vertex a(Vector(vector<float>({1.0f,1.0f,1.0f,1.0f})), Colour(255,0,0));
    // Vertex b(Vector(vector<float>({2.0f,1.0f,1.0f,1.0f})), Colour(0,255,0));
    // Vertex c(Vector(vector<float>({1.0f,2.0f,1.0f,1.0f})), Colour(0,0,255));
    // Triangle3D triangle(a, b, c);
    // Model model(vector<Triangle3D>({triangle}));
    // Object3D obj(model, Vector(vector<float>({0.0f,0.0f,2.0f,1.0f})), shaderPtr);
    Object3D obj = createCube(Vector(vector<float>({1.0f,1.5f,2.0f,1.0f})), shaderPtr);
    obj.scale(Vector(vector<float>({1.0f,0.5f,1.0f})));
    scene.addObject(obj);

    // Initialise the display
    shared_ptr<FragmentBuffer> fragmentBufferPtr(new FragmentBuffer(width, height));
    XtermDisplay display(width, height, fragmentBufferPtr);
    display.initialise();

    for(int i = 0; i < 60; ++i) {
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