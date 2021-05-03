#include "scene.h"
#include "display.h"
#include "fragment_buffer.h"
#include "camera.h"

class Rendersaurus {
    public:
        Rendersaurus(unique_ptr<Display> displayPtr, shared_ptr<Shader> shaderPtr);
        ~Rendersaurus();
        void initialise();
        void addObject(const Object3D& object);
        void refresh();
    private:
        Camera camera;
        Scene scene;
        unique_ptr<Display> displayPtr;
        shared_ptr<Shader> shaderPtr;
        shared_ptr<FragmentBuffer> fragmentBufferPtr;
        bool initialised;
};