#include "scene.h"
#include "display.h"
#include "fragment_buffer.h"
#include "camera.h"

class Rendersaurus {
    public:
        Rendersaurus(std::unique_ptr<Display> displayPtr, std::shared_ptr<Shader> shaderPtr);
        ~Rendersaurus();
        void initialise();
        void addObject(std::shared_ptr<const Object3D> objectPtr);
        int refresh();
    private:
        Camera camera;
        Scene scene;
        std::unique_ptr<Display> displayPtr;
        std::shared_ptr<Shader> shaderPtr;
        std::shared_ptr<FragmentBuffer> fragmentBufferPtr;
        bool initialised;
};