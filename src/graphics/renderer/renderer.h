#pragma once
#include "../buffers/buffers.h"
#include "../camera/camera.h"
#include "../mesh/mesh.h"
#include "../shaders/shaders.h"

class Renderer {

    public:
        Renderer();
        ~Renderer();

        void draw(VertexArray &vertexArray, IndexBuffer &indexBuffer,
                  Shader &shader);
        void draw(VertexArray &vertexArray, Shader &shader,
                  unsigned int vertexCount);
        void draw(Actor &actor, Mesh &mesh, Camera &camera);
        // void draw(Actor &actor, Mesh &mesh);
        void clear();

    private:
        bool indexUsed = false;
        bool used = false;
        unsigned int lastArrayId = 0;
        unsigned int lastShaderId = 0;
        unsigned int lastIndexId = 0;
};
