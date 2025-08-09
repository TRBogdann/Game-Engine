#define GLM_ENABLE_EXPERIMENTAL
#include "transformations.h"
#include "../settings.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

glm::mat4 Transform::rotation(glm::vec3 angles) {
    if (Program_Settings::transformation_mode == Quaternion_Mode) {
        glm::quat qX = glm::angleAxis(angles[0], glm::vec3(1, 0, 0));
        glm::quat qY = glm::angleAxis(angles[1], glm::vec3(0, 1, 0));
        glm::quat qZ = glm::angleAxis(angles[2], glm::vec3(0, 0, 1));

        glm::quat q = glm::normalize(qZ * qY * qX);

        return glm::toMat4(q);
    }

    else {
        glm::mat4 rotX =
        glm::rotate(glm::mat4(1.0f), angles[0], glm::vec3(1, 0, 0));
        glm::mat4 rotY =
        glm::rotate(glm::mat4(1.0f), angles[1], glm::vec3(0, 1, 0));
        glm::mat4 rotZ =
        glm::rotate(glm::mat4(1.0f), angles[2], glm::vec3(0, 0, 1));

        return rotZ * rotY * rotX;
    }
}
