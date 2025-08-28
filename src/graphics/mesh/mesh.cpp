#include "mesh.h"
#include "../buffers/buffers.h"
#include "../blender/blender.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

Actor::Actor(glm::vec3 position, glm::vec3 scale)
    : position(position),
      scale(scale) {}

Actor::Actor():position({0.0,0.0,0.0}),scale({0.0,0.0,0.0})
{
    
}

Actor::~Actor() {}

void Actor::setPosition(glm::vec3 position) { this->position = position; }
void Actor::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
void Actor::setScale(glm::vec3 scale) { this->scale = scale; }
void Actor::setUniqueShader(Shader *shader) { this->uniqueShader = shader; }

glm::vec3 Actor::getPosition() { return this->position; }
glm::vec3 Actor::getRotation() { return this->rotation; }
glm::vec3 Actor::getScale() { return this->scale; }
Shader *Actor::getUniqueShader() { return this->uniqueShader; }

Mesh::Mesh(float *data, unsigned long size, Shader *globalShader,
           int nOfAtrbutes, GraphicalAtribute *atributes, bool keepData) {

    int dim = 0;
    for (int i = 0; i < nOfAtrbutes; i++) {
        dim += atributes[i].getSize();
    }

    this->globalShader = globalShader;
    this->vertexArray = new VertexArray(dim * sizeof(float));
    this->vertexArray->bind();
    this->vertexBuffer = new VertexBuffer(data, size * sizeof(float));
    this->vertexBuffer->bind();
    this->vertexArray->addData(*this->vertexBuffer, atributes, nOfAtrbutes);
    this->vertexCount = size / dim;

    if (keepData) {
        this->size = size;
        this->data = new float[size];
        for (int i = 0; i < size; i++) {
            this->data[i] = data[i];
        }
    }
}

Mesh::~Mesh() {
    if (this->data) {
        delete[] this->data;
    }

    if (this->indexData) {
        delete[] this->indexData;
    }

    if (this->vertexArray) {
        delete vertexArray;
    }

    if (this->vertexBuffer) {
        delete vertexBuffer;
    }

    if (this->indexBuffer) {
        delete indexBuffer;
    }
}

Mesh::Mesh() {}
// TODO - Add check for file (exists,fileFormat,fileSize) so no buffer overflow
// or crash
Mesh *Mesh::loadMesh(std::string filePath, unsigned char file_format,
                     Shader *globalShader, int nOfAtrbutes,
                     GraphicalAtribute *atributes, bool keepData) {
    float *data = nullptr;
    int vertexSize;
    std::ifstream f(filePath);
    std::stringstream buff;
    buff << f.rdbuf();
    std::string temp;
    // TODO - add formats
    switch (file_format) {
    case ENGINE_SIMPLE_FILE_FORMAT: {
        int i = -1;
        while (std::getline(buff, temp, ',')) {
            temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
            if (i == -1) {
                vertexSize = std::stoi(temp);
                data = new float[vertexSize];
            } else if (i < vertexSize) {
                data[i] = std::stof(temp);
            }
            i++;
        }
        break;
    }

    case WAVEFRONT_FILE_FORMAT:
        return Blender::loadWavefront(filePath,globalShader,keepData);
    }
    
    if (!data) {
        return nullptr;
    }

    Mesh *mesh = new Mesh();

    int dim = 0;
    for (int i = 0; i < nOfAtrbutes; i++) {
        dim += atributes[i].getSize();
    }

    mesh->globalShader = globalShader;
    mesh->vertexArray = new VertexArray(dim * sizeof(float));
    mesh->vertexArray->bind();
    mesh->vertexBuffer = new VertexBuffer(data, vertexSize * sizeof(float));
    mesh->vertexBuffer->bind();
    mesh->vertexArray->addData(*(mesh->vertexBuffer), atributes, nOfAtrbutes);
    mesh->vertexCount = vertexSize / dim;

    if (keepData) {
        mesh->size = vertexSize;
        mesh->data = data;
    } else {
        delete[] data;
    }

    return mesh;
}

void Mesh::setTexture(Texture *texture) { this->texture = texture; }
void Mesh::setIndexBuffer(unsigned int *data, unsigned long size,
                          bool keepData) {
    this->indexBuffer = new IndexBuffer(data, size);
    this->indexBuffer->bind();

    if (keepData) {
        this->indexData = new unsigned int(size);
        for (int i = 0; i < size; i++) {
            this->indexData[i] = data[i];
        }
        this->indexSize = size;
    }
};

void Mesh::refresh() {
    if (this->vertexBuffer && this->data) {
        this->vertexBuffer->update(this->data, this->size * sizeof(float));
    }
}

unsigned int Mesh::getVertexCount() { return this->vertexCount; }
float *Mesh::Data() { return this->data; }
unsigned long Mesh::getDataSize() { return this->size; }

unsigned int *Mesh::IndexData() { return this->indexData; }
unsigned long Mesh::getIndexDataSize() { return this->indexSize; }

RenderMode Mesh::getRenderMode() { return this->renderMode; }
void Mesh::setRenderMode(RenderMode mode) { this->renderMode = mode; }

IndexBuffer *Mesh::getIndexBuffer() { return this->indexBuffer; }
VertexBuffer *Mesh::getVertexBuffer() { return this->vertexBuffer; }
VertexArray *Mesh::getVertexArray() { return this->vertexArray; }

ShapeRegistry::ShapeRegistry() {}

ShapeRegistry::~ShapeRegistry() {

    if (this->colorAtributes) {
        delete[] this->colorAtributes;
    }
    if (this->texAtributes) {
        delete[] this->texAtributes;
    }

    for (auto it = this->colorShaders.begin(); it != this->colorShaders.end();
         it++) {
        if (it->second) {
            delete it->second;
        }
    }
    for (auto it = this->textureShaders.begin();
         it != this->textureShaders.end(); it++) {
        if (it->second) {
            delete it->second;
        }
    }

    ShapeRegistry::collection = nullptr;
}

ShapeRegistry *ShapeRegistry::collection = nullptr;

ShapeRegistry *ShapeRegistry::getInstance() {
    if (!ShapeRegistry::collection) {
        ShapeRegistry::collection = new ShapeRegistry();
        collection->colorAtributes =
            GraphicalAtribute::getCreator()->createAtributes(SHADER_COLOR,
                                                             COORDINATES_XYZ);
        collection->texAtributes =
            GraphicalAtribute::getCreator()->createAtributes(SHADER_TEXTURE,
                                                             COORDINATES_XYZ);
    }

    return ShapeRegistry::collection;
}

bool ShapeRegistry::exists(std::string id) {
    auto it = this->meshes.find(id);
    return it != this->meshes.end();
}

Mesh *ShapeRegistry::getShape(SHAPE_NAME name, SHADER_TYPE type,
                              DEFAULT_SHADER shader_name, bool saveData) {
    std::string id = std::to_string(name) + "_" + std::to_string(type);
    if (exists(id)) {
        return this->meshes[id];
    }
    std::string home = std::getenv("HOME");
    std::string path = home + "/.game-engine/default_mesh/";
    GraphicalAtribute *atributes;

    if (type == SHADER_COLOR) {
        path += "color/";
        atributes = this->colorAtributes;
    } else if (type == SHADER_TEXTURE) {
        path += "texture/";
        atributes = this->texAtributes;
    } else {
        return nullptr;
    }

    switch (name) {
    case SHAPE_TRIANGLE:
        path += "triangle.obj";
        break;
    case SHAPE_RECTANGLE:
        path += "rectangle.obj";
        break;
    case SHAPE_CIRCLE:
        assert("Circle object doesn t exist yet");
        path += "circle.obj";
        break;
    case SHAPE_CUBE:
        path += "cube.obj";
    case SHAPE_PYRAMID:
        assert("Pyramid object doesn t exist yet");
        break;
        path += "pyramid.obj";
    case SHAPE_SPHERE:
        assert("Sphere object doesn t exist yet");
        path += "sphere.obj";
        break;
    default:
        return nullptr;
    }

    auto shaders =
        type == SHADER_COLOR ? this->colorShaders : this->textureShaders;
    auto it = shaders.find(shader_name);
    Shader *shader;
    if (it == shaders.end()) {
        shader = Shader::getCreator()->createShader(shader_name, type,
                                                    COORDINATES_XYZ);
        shaders.insert(
            std::pair<DEFAULT_SHADER, Shader *>(shader_name, shader));
    } else {
        shader = shaders[shader_name];
    }
    Mesh *mesh = Mesh::loadMesh(path, ENGINE_SIMPLE_FILE_FORMAT, shader, 2,
                                atributes, saveData);
    return mesh;
}
