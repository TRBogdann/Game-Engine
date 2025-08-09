#pragma once
#include <GameEngine/Graphics/mesh.h>

namespace Surface {
Mesh *generateFlatSurface(unsigned int nOfQuadsW, unsigned int nOfQuadsH,
                          Shader *shader, SHADER_TYPE type,
                          bool keepData = false);

Mesh *generateFlatConstantSurface(unsigned int nOfQuadsW,
                                  unsigned int nOfQuadsH, Shader *shader,
                                  SHADER_TYPE type, bool keepData = false);

} // namespace Surface
