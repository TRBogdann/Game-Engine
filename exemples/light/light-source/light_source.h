
#include <glm/ext/vector_float3.hpp>
#include "../../../src/graphics/shaders/shaders.h"
#include "../../../src/graphics/mesh/mesh.h"
#include "../../../src/graphics/renderer/renderer.h"
#include <string>

class LightSource
{
    public:
    LightSource(std::string path,Shader* shader,glm::vec3 position,glm::vec3 scale);
    ~LightSource();

    void draw(Renderer &renderer,Camera &camera);
    Shader* getShader();
    void  setShader(Shader* shader);
    glm::vec3 position();
    glm::vec3 scale();
    
    static float ambient;
    static float specularStrength;

    private:
    LightSource(const LightSource& source) = delete;
    LightSource& operator=(const LightSource& source) = delete;
    Mesh* mesh;
    Shader* shader;
    Actor source[40];

};