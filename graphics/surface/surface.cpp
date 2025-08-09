#include "surface.h"
#include "../macros.h"

float texturedFlatSurface[] = {
    -0.5f, 0.0,  -0.5f, 0.0f, 1.0f, 0.5f,  0.0f, -0.5f, 1.0f, 1.0f,
    0.5f,  0.0f, 0.5f,  1.0f, 0.0f, 0.5f,  0.0f, 0.5f,  1.0f, 0.0f,
    -0.5f, 0.0f, 0.5f,  0.0f, 0.0f, -0.5f, 0.0f, -0.5f, 0.0f, 1.0f};

// Create a color uniform shader;
Mesh *Surface::generateFlatSurface(unsigned int nOfQuadsW,
                                   unsigned int nOfQuadsH, Shader *shader,
                                   SHADER_TYPE type, bool keepData) {
    float *data;
    unsigned int vertexSize;

    if (type == SHADER_COLOR) {
        vertexSize = 7;
    } else if (type == SHADER_TEXTURE) {
        vertexSize = 5;
    } else {
        return nullptr;
    }

    data = new float[6 * vertexSize * nOfQuadsW * nOfQuadsH];

    //(1-(-1))/nOfQuads;
    float stepW = 2.0f / nOfQuadsW;
    float stepH = 2.0f / nOfQuadsH;
    unsigned int step = vertexSize * 6;
    unsigned int k = 0;

    for (int i = 0; i < nOfQuadsH; i++)
        for (int j = 0; j < nOfQuadsW; j++) {

            float minH = -1.0f + stepH * i;
            float maxH = -1.0f + stepH * (i + 1);
            float minW = -1.0f + stepW * j;
            float maxW = -1.0f + stepW * (j + 1);

            for (int vert = 0; vert < 6; vert += 1) {

                data[k + vert * vertexSize] =
                    texturedFlatSurface[vert * 5] == -0.5f ? minW : maxW;
                data[k + vert * vertexSize + 1] = 0.0f;
                data[k + vert * vertexSize + 2] =
                    texturedFlatSurface[vert * 5 + 2] == -0.5f ? minH : maxH;

                if (type == SHADER_COLOR) {
                    data[k + vert * vertexSize + 3] = 1.0f;
                    data[k + vert * vertexSize + 4] = 0.0f;
                    data[k + vert * vertexSize + 5] = 0.0f;
                    data[k + vert * vertexSize + 6] = 1.0f;
                }

                else {
                    data[k + vert * vertexSize + 3] =
                        texturedFlatSurface[vert * vertexSize + 3];
                    data[k + vert * vertexSize + 4] =
                        texturedFlatSurface[vert * vertexSize + 4];
                }
            }

            k += step;
        };

    GraphicalAtribute *atributes =
        GraphicalAtribute::getCreator()->createAtributes(type, COORDINATES_XYZ);
    Mesh *mesh = new Mesh(data, 6 * vertexSize * nOfQuadsW * nOfQuadsH, shader,
                          2, atributes, keepData);
    delete[] atributes;
    delete[] data;
    return mesh;
}

Mesh *Surface::generateFlatConstantSurface(unsigned int nOfQuadsW,
                                           unsigned int nOfQuadsH,
                                           Shader *shader, SHADER_TYPE type,
                                           bool keepData) {
    float *data;
    unsigned int vertexSize;

    if (type == SHADER_COLOR) {
        vertexSize = 7;
    } else if (type == SHADER_TEXTURE) {
        vertexSize = 5;
    } else {
        return nullptr;
    }

    data = new float[6 * vertexSize * nOfQuadsW * nOfQuadsH];

    //(1-(-1))/nOfQuads; for coodinates
    //(1-0)/nOfQuads; for texture
    float stepTextureW = 1.0f / nOfQuadsW;
    float stepTextureH = 1.0f / nOfQuadsH;
    float stepW = 2.0f / nOfQuadsW;
    float stepH = 2.0f / nOfQuadsH;
    unsigned int step = vertexSize * 6;
    unsigned int k = 0;

    for (int i = 0; i < nOfQuadsH; i++)
        for (int j = 0; j < nOfQuadsW; j++) {

            float minH = -1.0f + stepH * i;
            float maxH = -1.0f + stepH * (i + 1);
            float minW = -1.0f + stepW * j;
            float maxW = -1.0f + stepW * (j + 1);

            float maxTextureH = 1.0f - stepTextureH * i;
            float minTextureW = 0.0f + stepTextureW * j;

            for (int vert = 0; vert < 6; vert += 1) {

                data[k + vert * vertexSize] =
                    texturedFlatSurface[vert * 5] == -0.5f ? minW : maxW;
                data[k + vert * vertexSize + 1] = 0.0f;
                data[k + vert * vertexSize + 2] =
                    texturedFlatSurface[vert * 5 + 2] == -0.5f ? minH : maxH;

                if (type == SHADER_COLOR) {
                    data[k + vert * vertexSize + 3] = 1.0f;
                    data[k + vert * vertexSize + 4] = 0.0f;
                    data[k + vert * vertexSize + 5] = 0.0f;
                    data[k + vert * vertexSize + 6] = 1.0f;
                }

                else {
                    data[k + vert * vertexSize + 3] =
                        minTextureW +
                        texturedFlatSurface[vert * vertexSize + 3] *
                            stepTextureW;
                    data[k + vert * vertexSize + 4] =
                        maxTextureH - stepTextureH +
                        texturedFlatSurface[vert * vertexSize + 4] *
                            stepTextureH;
                }
            }

            k += step;
        };

    GraphicalAtribute *atributes =
        GraphicalAtribute::getCreator()->createAtributes(type, COORDINATES_XYZ);
    Mesh *mesh = new Mesh(data, 6 * vertexSize * nOfQuadsW * nOfQuadsH, shader,
                          2, atributes, keepData);
    delete[] atributes;
    delete[] data;
    return mesh;
}
