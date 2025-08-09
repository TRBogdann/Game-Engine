#include "renderer.h"
#include "../settings.h"
#include "../transformations/transformations.h"
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::draw(VertexArray &vertexArray, IndexBuffer &indexBuffer,
                    Shader &shader) {
    if (!this->used || this->lastShaderId != shader.getRendererId()) {
        shader.bind();
        this->used = true;
        this->lastShaderId = shader.getRendererId();
    }

    if (!this->used || this->lastArrayId != vertexArray.getRendererId()) {
        vertexArray.bind();
        this->used = true;
        this->lastArrayId = vertexArray.getRendererId();
    }

    if (!this->indexUsed || this->lastIndexId != indexBuffer.getRendererId()) {
        indexBuffer.bind();
        this->indexUsed = true;
        this->lastIndexId = indexBuffer.getRendererId();
    }

    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT,
                   nullptr);
}

void Renderer::draw(VertexArray &vertexArray, Shader &shader,
                    unsigned int vertexCount) {

    if (!this->used || this->lastShaderId != shader.getRendererId()) {
        shader.bind();
        this->used = true;
        this->lastShaderId = shader.getRendererId();
    }

    if (!this->used || this->lastArrayId != vertexArray.getRendererId()) {
        vertexArray.bind();
        this->used = true;
        this->lastArrayId = vertexArray.getRendererId();
    }

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Renderer::draw(Actor &actor, Mesh &mesh, Camera &camera) {

    Shader *shader = mesh.globalShader;
    if (actor.getUniqueShader()) {
        shader = actor.getUniqueShader();
    }
    if (!this->used || this->lastShaderId != shader->getRendererId()) {
        shader->bind();
        this->used = true;
        this->lastShaderId = shader->getRendererId();
    }

    if (!this->used || this->lastArrayId != mesh.vertexArray->getRendererId()) {
        mesh.vertexArray->bind();
        this->used = true;
        this->lastArrayId = mesh.vertexArray->getRendererId();
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, actor.getPosition());
    model = model * Transform::rotation(actor.getRotation());
    model = glm::scale(model, actor.getScale());
    glm::mat4 view = camera.getView();
    glm::mat4 projection = camera.getProjection(Program_Settings::aspectRatio);

    shader->setUniformMat4("model", model);
    shader->setUniformMat4("view", view);
    shader->setUniformMat4("projection", projection);

    if (mesh.indexBuffer != nullptr) {
        if (!this->indexUsed ||
            this->lastIndexId != mesh.indexBuffer->getRendererId()) {
            mesh.indexBuffer->bind();
            this->indexUsed = true;
            this->lastIndexId = mesh.indexBuffer->getRendererId();
        }
        glDrawElements(GL_TRIANGLES, mesh.indexBuffer->getCount(),
                       GL_UNSIGNED_INT, nullptr);

    } else {
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }
}

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }
