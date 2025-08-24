#pragma once
#include <GameEngine/Graphics/buffers.h>
#include <GameEngine/Graphics/macros.h>
#include <GameEngine/Graphics/shaders.h>
#include <GameEngine/Graphics/texture.h>
#include <map>
#include <string>

// Todo
enum RenderMode { RM_AUTO, RM_NONE };

class Mesh {
    public:
        Mesh(float *data, unsigned long size, Shader *globalShader,
             int nOfAtrbutes, GraphicalAtribute *atributes,
             bool keepData = false);
        ~Mesh();

        static Mesh *loadMesh(std::string filePath, FILE_FORMAT file_format,
                              Shader *globalShader, int nOfAtrbutes,
                              GraphicalAtribute *atributes,
                              bool keepData = false);

        void setRenderMode(RenderMode mode);
        void setTexture(Texture *texture);
        void setIndexBuffer(unsigned int *data, unsigned long size,
                            bool keepData = false);
        // void changeColor(unsigned char r, unsigned char g, unsigned char g,
        // unsigned char a)
        void refresh();
        float *Data();
        unsigned long getDataSize();
        unsigned int *IndexData();
        unsigned long getIndexDataSize();
        RenderMode getRenderMode();
        unsigned int getVertexCount();
        friend class Renderer;
        VertexArray *getVertexArray();
        IndexBuffer *getIndexBuffer();
        VertexBuffer *getVertexBuffer();

    private:
        Mesh();
        Mesh(const Mesh &mesh) = delete;
        Mesh &operator=(const Mesh &mesh) = delete;
        unsigned int vertexCount = 0;
        RenderMode renderMode = RM_AUTO;
        float *data = nullptr;
        unsigned int *indexData = nullptr;
        unsigned long size = 0;
        unsigned long indexSize = 0;
        Shader *globalShader;
        VertexArray *vertexArray;
        VertexBuffer *vertexBuffer;
        IndexBuffer *indexBuffer = nullptr;
        Texture *texture = nullptr;
};

class Actor {
    public:
        Actor(glm::vec3 position, glm::vec3 scale);
        Actor();
        ~Actor();
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();
        Shader *getUniqueShader();

        void setUniqueShader(Shader *shader);
        void setPosition(glm::vec3 position);
        void setRotation(glm::vec3 rotation);
        void setScale(glm::vec3 scale);

    private:
        Shader *uniqueShader = nullptr;
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 position;
        glm::vec3 scale;
};

// TODO - Make it thread-safe
class ShapeRegistry {
    public:
        ~ShapeRegistry();
        static ShapeRegistry *getInstance();
        Mesh *getShape(SHAPE_NAME shape_name, SHADER_TYPE type,
                       DEFAULT_SHADER shader_name = -1, bool saveData = false);

    private:
        bool exists(std::string id);
        ShapeRegistry(const ShapeRegistry &) = delete;
        ShapeRegistry &operator=(const ShapeRegistry &) = delete;
        ShapeRegistry();
        std::map<DEFAULT_SHADER, Shader *> colorShaders;
        std::map<DEFAULT_SHADER, Shader *> textureShaders;
        GraphicalAtribute *texAtributes;
        GraphicalAtribute *colorAtributes;
        std::map<std::string, Mesh *> meshes;
        static ShapeRegistry *collection;
};
/*
 * template<typename id_type> class InstanceRegistry
 * {
 *
 * private:
 *    std::map<id_type, glm::vec3> instances;
 * }
 */
