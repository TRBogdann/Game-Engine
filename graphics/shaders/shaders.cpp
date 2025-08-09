#include "shaders.h"
#include "../../files/files.h"
#include <GL/glew.h>
#include <cstdlib>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

unsigned int Shader::compileShader(const std::string &source,
                                   unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Verificare erori
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        if (type == GL_VERTEX_SHADER) {
            std::cout << "[Vertex Shader] : ";
        }

        else if (type == GL_FRAGMENT_SHADER) {
            std::cout << "[Fragment Shader] : ";
        }

        else {
            std::cout << "[Unknown Shader] : ";
        }

        int message_lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &message_lenght);
        char *message = (char *)alloca(message_lenght * sizeof(char));

        std::cout << "Failed to compile shader" << '\n';
        std::cout << message << '\n';
        std::cout << source;

        glDeleteShader(id);

        return 0;
    }

    return id;
}

Shader::Shader(const std::string &vertexShader,
               const std::string &fragmentShader) {

    rendererId = glCreateProgram();

    _vertexShader = vertexShader;
    _fragmentShader = fragmentShader;

    unsigned int vshader = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fshader = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(rendererId, vshader);
    glAttachShader(rendererId, fshader);

    glLinkProgram(rendererId);
    glValidateProgram(rendererId);

    glDeleteShader(vshader);
    glDeleteShader(fshader);
};

Shader::~Shader() {}

void Shader::bind() { glUseProgram(rendererId); }

void Shader::unbind() { glUseProgram(0); }

void Shader::setUniform4f(std::string name, float r, float g, float b,
                          float a) {
    glUniform4f((findUniform(name)), r, g, b, a);
}

void Shader::setUniform1f(std::string name, float slot) {
    glUniform1f((findUniform(name)), slot);
}

void Shader::setUniform1i(std::string name, int slot) {
    glUniform1i((findUniform(name)), slot);
}

void Shader::setUniformMat4(std::string name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(findUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::findUniform(std::string name) {
    int location = glGetUniformLocation(rendererId, name.c_str());
    if (location == -1) {
        std::cerr << "\n[ERROR]: Invalid uniform location";
    }

    return location;
}

Shader::ShaderCreator::ShaderCreator() {}

Shader::ShaderCreator::~ShaderCreator() { Shader::creator = nullptr; }

Shader::ShaderCreator *Shader::creator = nullptr;

Shader::ShaderCreator *Shader::getCreator() {
    if (Shader::creator == nullptr) {
        creator = new Shader::ShaderCreator();
    }

    return creator;
}

Shader *Shader::ShaderCreator::createShader(DEFAULT_SHADER shaderName,
                                            SHADER_TYPE type,
                                            COORDINATES_FORMAT format) {

    std::string home = std::getenv("HOME");
    std::string pathVertex = format == COORDINATES_XYZ
                                 ? home + "/.game-engine/default_shaders/xyz/"
                                 : home + "/.game-engine/default_shaders/xyzw/";
    std::string pathFragment =
        home + "/.game-engine/default_shaders/fragments/";
    std::string typeStr = type == SHADER_COLOR ? "color" : "texture";
    std::string nameStrVert = "";
    std::string nameStrFrag = "";

    Shader *shader = nullptr;

    switch (shaderName) {
    case SIMPLE_SHADER:
        nameStrVert = "default_";
        nameStrFrag = "default_";
        break;

    case MVP_SHADER:
        nameStrVert = "mvp_";
        nameStrFrag = "default_";
        break;

    case CLIP_MODEL_SHADER:
        nameStrVert = "clip_model_";
        nameStrFrag = "clip_model_";
    }

    if (nameStrFrag != "" && nameStrVert != "") {
        std::string tempVert = pathVertex + nameStrVert + typeStr + ".vert";
        std::string tempFrag = pathFragment + nameStrFrag + typeStr + ".frag";

        std::ifstream vertexFile(tempVert);
        std::ifstream fragmentFile(tempFrag);

        std::string vertexShader = FileToString(vertexFile);
        std::string fragmentShader = FileToString(fragmentFile);

        shader = new Shader(vertexShader, fragmentShader);
    }

    return shader;
}

unsigned int Shader::getRendererId() { return this->rendererId; }
