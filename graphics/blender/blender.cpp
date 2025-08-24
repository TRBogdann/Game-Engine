#include "./blender.h"
#include "../../cpu-math/math.h"
#include "../../string-utils/string_utils.h"
#include "../../exceptions/exceptions.h"
#include <fstream>
#include <string>
#include <vector>

using StringUtils::StringTokenizer;

namespace Blender {

    VertexNormalIndices::VertexNormalIndices(const std::string& line):indices(nullptr),nOfVertices(0)
    {
        std::string trimmed = StringUtils::trim(line);
        StringTokenizer tokenizer(trimmed," ");

        if(tokenizer.length() > 1)
        {
            this->nOfVertices = tokenizer.length()-1;
            this->indices = new unsigned int*[this->nOfVertices];
            for(int i=1; i<tokenizer.length(); i++)
            {
                StringTokenizer vertexIndices(StringUtils::trim(tokenizer[i]),"/");
                if(vertexIndices.length()!=3)
                {
                    throw FileException(
                        FileException::BAD_FILE_FORMAT,
                        "[Blender::VertexNormalIndices]: Bad file format (line: "+line+")"
                    );
                }

                this->indices[i-1] = new unsigned int[3];

                this->indices[i-1][0] = std::stoi(vertexIndices[0]);
                this->indices[i-1][1] = std::stoi(vertexIndices[1]);
                this->indices[i-1][2] = std::stoi(vertexIndices[2]);
            }
        }
    }

    VertexNormalIndices::VertexNormalIndices():indices(nullptr),nOfVertices(0)
    {

    }

    VertexNormalIndices::VertexNormalIndices(const VertexNormalIndices& vni):indices(nullptr),nOfVertices(0)
    {
        if(vni.indices)
        {
            this->nOfVertices = vni.nOfVertices;
            this->indices = new unsigned int*[this->nOfVertices];
            for(int i=0; i<this->nOfVertices; i++)
            {
                this->indices[i] = new unsigned int[3];
                for(int j=0; j<3; j++)
                {
                    this->indices[i][j] = vni.indices[i][j];
                }
            }
        }
    }

    VertexNormalIndices& VertexNormalIndices::operator=(const VertexNormalIndices& vni)
    {
        if(this->indices)
        {
            for(int i=0; i<this->nOfVertices;i++)
            {
                delete[] this->indices[i];
            }
            delete[] this->indices;

            this->indices = nullptr;
            this->nOfVertices = 0;
        }

        if(vni.indices)
        {
            this->nOfVertices = vni.nOfVertices;
            this->indices = new unsigned int*[this->nOfVertices];
            for(int i=0; i<this->nOfVertices; i++)
            {
                this->indices[i] = new unsigned int[3];
                for(int j=0; j<3; j++)
                {
                    this->indices[i][j] = vni.indices[i][j];
                }
            }
        }

        return *this;
    }

    unsigned int VertexNormalIndices::size() const
    {
        return this->nOfVertices;
    }


    VertexNormalIndices& VertexNormalIndices::operator=(std::pair<unsigned int**,unsigned int> data)
    {
        if(this->indices)
        {
            for(int i=0; i<this->nOfVertices;i++)
            {
                delete[] this->indices[i];
            }
            delete[] this->indices;

            this->indices = nullptr;
            this->nOfVertices = 0;
        }

        this->indices = data.first;
        this->nOfVertices = data.second;

        return *this;
    }

    unsigned int* VertexNormalIndices::getIndices(unsigned int index)
    {
        if(this->indices == nullptr)
        {
            return nullptr;
        }

        if(index >= this->nOfVertices)
        {
            return nullptr;
        }

        return this->indices[index];
    }

    
    VertexNormalIndices::~VertexNormalIndices()
    {
        if(this->indices)
        {
            for(int i=0; i<this->nOfVertices;i++)
            {
                delete[] this->indices[i];
            }
            delete[] this->indices;
        }
    }

    GraphicalAtribute* createAtributes()
    {
        GraphicalAtribute* atributes = new GraphicalAtribute[3];
        
        atributes[0].name = "Vertices";
        atributes[0].size = 3;

        atributes[1].name = "Texture";
        atributes[1].size = 2;

        atributes[2].name = "Normal";
        atributes[2].size = 3;

        return atributes;
    }

    Mesh* loadWavefront(std::string filepath,Shader* shader,bool keepData)
    {
        std::vector<Math::vec3f> positions;
        std::vector<Math::vec2f> textures;
        std::vector<Math::vec3f> normals;
        std::vector<VertexNormalIndices> faces;
        unsigned int indexCount=0,vertexCount=0;
        unsigned int* indexData = nullptr;
        float* data = nullptr;

        std::ifstream f(filepath);
        std::string line;
        while(std::getline(f,line))
        {
            StringTokenizer tokenizer(StringUtils::trim(line)," ");
            if(tokenizer.length() == 0)
            {
                continue;
            }

            if(tokenizer[0]=="v")
            {
                if(tokenizer.length()!=4) throw FileException(
                FileException::BAD_FILE_FORMAT,
                "[Blender::loadWavefront]: Bad line format ("+line+")"
                );
                
                positions.push_back(Math::vec3f(
                    std::stof(tokenizer[1]),
                    std::stof(tokenizer[2]),
                    std::stof(tokenizer[3])
                ));
            }
            else if(tokenizer[0]=="vt")
            {
                if(tokenizer.length()!=3) throw FileException(
                FileException::BAD_FILE_FORMAT,
                "[Blender::loadWavefront]: Bad line format ("+line+")"
                );
                
                textures.push_back(Math::vec2f(
                    std::stof(tokenizer[1]),
                    std::stof(tokenizer[2])
                ));
            }
            else if(tokenizer[0]=="vn")
            {
                if(tokenizer.length()!=4) throw FileException(
                FileException::BAD_FILE_FORMAT,
                "[Blender::loadWavefront]: Bad line format ("+line+")"
                );
                
                
                normals.push_back(Math::vec3f(
                    std::stof(tokenizer[1]),
                    std::stof(tokenizer[2]),
                    std::stof(tokenizer[3])
                ));
            }
            else if(tokenizer[0]=="f")
            {
                VertexNormalIndices vni(line);
                vertexCount+=vni.size();
                indexCount+= (vni.size()-2)*3;
                faces.push_back(vni);
            }
        }

        data = new float[vertexCount*BLENDER_VERTEX_SIZE];
        indexData = new unsigned int[indexCount];

        unsigned int currentIndex = 0;
        unsigned int index = 0;
        for(auto& vni: faces)
        {
            
            if(vni.size()==3)
            {
                indexData[index] = currentIndex;  
                indexData[index+1] = currentIndex+1;
                indexData[index+2] = currentIndex+2;

                index+=3;
            }
            else 
            {
                //Triangle1
                indexData[index] = currentIndex;  
                indexData[index+1] = currentIndex+1;
                indexData[index+2] = currentIndex+2;

                //Triangle2
                indexData[index+3] = currentIndex;  
                indexData[index+4] = currentIndex+2;
                indexData[index+5] = currentIndex+3;

                index+=6;
            }

            for(int i=0; i<vni.size(); i++)
            {
                unsigned int* indices = vni.getIndices(i);
                
                Math::vec3f position = positions[indices[0]-1];
                data[currentIndex*BLENDER_VERTEX_SIZE] = position.x;
                data[currentIndex*BLENDER_VERTEX_SIZE+1] = position.y;
                data[currentIndex*BLENDER_VERTEX_SIZE+2] = position.z;

                Math::vec2f texture = textures[indices[1]-1];
                data[currentIndex*BLENDER_VERTEX_SIZE+3] = texture.x;
                data[currentIndex*BLENDER_VERTEX_SIZE+4] = texture.y;

                Math::vec3f normal = normals[indices[2]-1];
                data[currentIndex*BLENDER_VERTEX_SIZE+5] = normal.x;
                data[currentIndex*BLENDER_VERTEX_SIZE+6] = normal.y;
                data[currentIndex*BLENDER_VERTEX_SIZE+7] = normal.z;

                
                currentIndex++;
                
            }            
        }
        
        


        GraphicalAtribute* atributes = createAtributes();
        Mesh* mesh = new Mesh(
            data, vertexCount*BLENDER_VERTEX_SIZE,
            shader, 
            BLENDER_ATRIBUTE_COUNT, atributes,
            keepData
        );

        mesh->setIndexBuffer(indexData, indexCount);


        delete[] atributes;
        delete[] data;
        delete[] indexData;

        return mesh;
    }
}