#include "model.h"

void Model::modifyAxis(Mesh *mesh, float value, unsigned int offset,
                       unsigned int vertexSize, bool updateImediatly) {
    unsigned int size = mesh->getDataSize();
    float *data = mesh->Data();
    if (size <= 0 && !data)
        return;

    for (int i = 0; i < size; i += vertexSize) {
        data[i + offset] = value;
    }

    if (updateImediatly) {
        mesh->refresh();
    }
}

void Model::rotate(Mesh *mesh, unsigned int vertexSize, Math::vec3f axis,
                   float angle, bool updateImediatly) {
    unsigned int size = mesh->getDataSize();
    float *data = mesh->Data();
    if (size <= 0 && !data)
        return;

    for (int i = 0; i < size; i += vertexSize) {
        Math::vec3f temp(data[i + 0], data[i + 1], data[i + 2]);
        Math::rotate3F(temp, axis, angle);
        data[i + 0] = temp.x;
        data[i + 1] = temp.y;
        data[i + 2] = temp.z;
    }

    if (updateImediatly) {
        mesh->refresh();
    }
}
