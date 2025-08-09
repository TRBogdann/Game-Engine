#pragma once
#include "../macros.h"
#include "glm/glm.hpp"
#include <fstream>
#include <ostream>
#include <string>

class Shader {

    private:
        class ShaderCreator {
            public:
                ShaderCreator();
                ~ShaderCreator();
                Shader *createShader(DEFAULT_SHADER shaderName,
                                     SHADER_TYPE type,
                                     COORDINATES_FORMAT format);
        };

        unsigned int findUniform(std::string name);

        unsigned int rendererId;
        std::string _fragmentShader;
        std::string _vertexShader;
        static ShaderCreator *creator;

    public:
        Shader(const std::string &vertexShader,
               const std::string &fragmentShader);
        ~Shader();

        static ShaderCreator *getCreator();
        static unsigned int compileShader(const std::string &source,
                                          unsigned int type);

        void bind();
        void unbind();

        unsigned int getRendererId();

        void setUniformMat4(std::string name, const glm::mat4 &matrix);
        void setUniform4f(std::string name, float r, float g, float b, float a);
        void setUniform1i(std::string name, int slot);
        void setUniform1f(std::string name, float slot);
};
