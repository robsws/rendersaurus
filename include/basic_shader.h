#include "shader.h"
#include "vertex.h"
#include "fragment.h"
#include "coord.h"

class BasicShader : public Shader {
    public:
        BasicShader(int width, int height);
    private:
        Vertex transformVertex(const Vertex& vertex) const;
        Fragment computeFragmentColour(const Coord& position, const Vertex& interpolatedVertex) const;
};