#include "texture.h"
#include <GL/eglew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../third_parties/stb_image.h"

Texture::Texture(const std::string filename, bool keepLocalData,
                 bool useOpacity)
: rendererId(0),
filePath(filename),
pixelBuffer(nullptr),
width(0),
height(0),
density(0),
opacity(useOpacity) {

    unsigned char *pixels =
    stbi_load(filePath.c_str(), &width, &height, &density, 4);

    glGenTextures(1, &rendererId);
    glBindTexture(GL_TEXTURE_2D, rendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
    GLfloat maxAniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
                    std::min(8.0f, maxAniso));

    glBindTexture(GL_TEXTURE_2D, 0);

    if (pixels) {
        stbi_image_free(pixels);
    }
}

Texture::~Texture() { glDeleteTextures(1, &rendererId); }

void Texture::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererId);
}

void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

int Texture::getDensity() { return density; }

int Texture::getWidth() { return width; }

int Texture::getHeight() { return height; }

unsigned int Texture::getRendererId() { return this->rendererId; }

void Texture::enableOpacity() { opacity = 1; }

void Texture::disableOpacity() { opacity = 0; }
