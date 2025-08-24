#include "light_source.h"
#include "../../../graphics/blender/blender.h"

float LightSource::ambient = 0.5;
float LightSource::specularStrength = 0.5;

LightSource::LightSource(std::string path,Shader* shader, glm::vec3 position,glm::vec3 scale)
{
    this->mesh = Blender::loadWavefront(path, shader);
    this->shader = shader;
    for (int i = 0; i < 40; i++) {
        this->source[i] =
            Actor(position,
                {scale.x + i / 4.0f, scale.y + i / 4.0f, scale.z + i / 4.0f});
    }
}

LightSource::~LightSource()
{
    if(this->mesh)
    {
        delete mesh;
    }
}

Shader* LightSource::getShader()
{
    return this->shader;
}

void LightSource::setShader(Shader* shader)
{
    this->shader = shader;
}

glm::vec3 LightSource::position()
{
    return this->source[0].getPosition();
}

glm::vec3 LightSource::scale()
{
    return this->source[0].getScale();
}

void LightSource::draw(Renderer &renderer,Camera &camera)
{
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        float col = 1.0f;
        for (int i = 0; i < 39; i++) {
            this->shader->setUniform4f("aColor", 
                col * 1.0f, col * 0.5f, 0.0f,col);
            renderer.draw(this->source[i], *this->mesh, camera);
            col *= 0.92f;
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}