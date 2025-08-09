#include "buffers.h"
#include <GL/glew.h>
GraphicalAtribute::GraphicalAtribute() {};

GraphicalAtribute::GraphicalAtribute(unsigned int size, std::string name)
    : name(name),
      size(size) {}
GraphicalAtribute::~GraphicalAtribute() {}

GraphicalAtribute::AtributeCreator *GraphicalAtribute::creator = nullptr;

std::string GraphicalAtribute::getName() { return this->name; }

unsigned int GraphicalAtribute::getSize() { return this->size; }

GraphicalAtribute::AtributeCreator *GraphicalAtribute::getCreator() {
    if (GraphicalAtribute::creator == nullptr) {
        GraphicalAtribute::creator = new GraphicalAtribute::AtributeCreator();
    }
    return creator;
}

GraphicalAtribute::AtributeCreator::AtributeCreator() {}

GraphicalAtribute::AtributeCreator::~AtributeCreator() {
    GraphicalAtribute::creator = nullptr;
}

GraphicalAtribute *
GraphicalAtribute::AtributeCreator::createAtributes(SHADER_TYPE type,
                                                    COORDINATES_FORMAT format) {
    GraphicalAtribute *atributes = nullptr;
    switch (type) {
    // TODO - ADD OTHER TYPES
    case SHADER_COLOR:
        atributes = new GraphicalAtribute[2];
        atributes[0].name = "Vertices";
        atributes[0].size = format;
        atributes[1].name = "Color";
        atributes[1].size = 4;
        this->nOfAtributes = 2;
        break;

    case SHADER_TEXTURE:
        atributes = new GraphicalAtribute[2];
        atributes[0].name = "Vertices";
        atributes[0].size = format;
        atributes[1].name = "Texture";
        atributes[1].size = 2;
        this->nOfAtributes = 2;
    }

    return atributes;
}

unsigned int GraphicalAtribute::AtributeCreator::getNOfAtributes() {
    return this->nOfAtributes;
}

VertexBuffer::VertexBuffer(const void *data, unsigned int byteSize) {

    glGenBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::update(const void *data, unsigned int byteSize,
                          unsigned int offset) {
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &rendererId); }

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, rendererId); }

void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

unsigned int VertexBuffer::getRendererId() { return this->rendererId; }

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int elementCount) {

    glGenBuffers(2, &rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(unsigned int),
                 data, GL_STATIC_DRAW);
    count = elementCount;
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(2, &rendererId); }

void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId); }

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

unsigned int IndexBuffer::getCount() { return count; }

unsigned int IndexBuffer::getRendererId() { return this->rendererId; }

VertexArray::VertexArray(unsigned int dataBlockByteSize)
    : dataSize(dataBlockByteSize) {

    glGenVertexArrays(1, &rendererId);
}

void VertexArray::bind() { glBindVertexArray(rendererId); }

void VertexArray::unbind() { glBindVertexArray(0); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &rendererId); }

void VertexArray::addData(VertexBuffer &buffer, GraphicalAtribute *atributes,
                          unsigned int atribCount) {

    buffer.bind();
    unsigned int offset = 0;
    for (int i = 0; i < atribCount; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, atributes[i].getSize(), GL_FLOAT, GL_FALSE,
                              dataSize, (GLvoid *)(offset * sizeof(float)));
        offset += atributes[i].getSize();
    }
}

unsigned int VertexArray::getRendererId() { return this->rendererId; }
