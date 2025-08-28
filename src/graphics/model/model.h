#pragma once
#include "../../cpu-math/math.h"
#include "../mesh/mesh.h"

namespace Model {
void modifyAxis(Mesh *mesh, float value, unsigned int offset,
                unsigned int vertexSize, bool updateImediatly = true);

void rotate(Mesh *mesh, unsigned int vertexSize, Math::vec3f axis, float angle,
            bool updateImediatly = true);
} // namespace Model
