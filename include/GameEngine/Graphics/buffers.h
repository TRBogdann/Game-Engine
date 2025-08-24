#pragma once
#include <GameEngine/Graphics/macros.h>
#include <string>



class GraphicalAtribute;
namespace Blender {
    GraphicalAtribute* createAtributes();
}

class GraphicalAtribute {
    private:
        GraphicalAtribute();
        class AtributeCreator {
            public:
                AtributeCreator();
                ~AtributeCreator();
                GraphicalAtribute *createAtributes(SHADER_TYPE type,
                                                   COORDINATES_FORMAT format);
                unsigned int getNOfAtributes();

            private:
                unsigned char nOfAtributes = 0;
        };
        unsigned int size;
        std::string name;
        static AtributeCreator *creator;

    public:
        friend GraphicalAtribute* Blender::createAtributes();
        GraphicalAtribute(unsigned int size, std::string name);
        ~GraphicalAtribute();
        std::string getName();
        unsigned int getSize();
        static AtributeCreator *getCreator();
};

class VertexBuffer {
    public:
        VertexBuffer(const void *data, unsigned int byteSize);
        ~VertexBuffer();

        void update(const void *data, unsigned int byteSize,
                    unsigned int offset = 0);
        void bind();
        void unbind();
        unsigned int getRendererId();

    private:
        unsigned int rendererId;
};

class IndexBuffer {
    public:
        IndexBuffer(const unsigned int *data, unsigned int elementCount);
        ~IndexBuffer();

        void bind();
        void unbind();

        unsigned int getCount();
        unsigned int getRendererId();

    private:
        unsigned int rendererId;
        unsigned int count;
};

class VertexArray {

    public:
        VertexArray(unsigned int dataBlockByteSize);
        ~VertexArray();

        void addData(VertexBuffer &buffer, GraphicalAtribute *atributes,
                     unsigned int atribCount);

        void bind();
        void unbind();

        unsigned int getRendererId();

    private:
        unsigned int dataSize;
        unsigned int rendererId;
};
