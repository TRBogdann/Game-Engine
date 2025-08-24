#include <string>
#include <GameEngine/Graphics/mesh.h>

#define BLENDER_VERTEX_SIZE 8
#define BLENDER_ATRIBUTE_COUNT 3

namespace Blender {
    class VertexNormalIndices
    {
        public:
        VertexNormalIndices();
        VertexNormalIndices(const std::string& line);
        VertexNormalIndices(const VertexNormalIndices& vni);
        VertexNormalIndices& operator=(const VertexNormalIndices& vni);
        VertexNormalIndices& operator=(std::pair<unsigned int**,unsigned int> data);
        ~VertexNormalIndices();

        unsigned int size() const;
        unsigned int* getIndices(unsigned int index);

        private:
        unsigned int** indices;
        unsigned int nOfVertices;
    };

    GraphicalAtribute* createAtributes();
    Mesh* loadWavefront(std::string filepath,Shader* shader=nullptr,bool keepData = false);
}