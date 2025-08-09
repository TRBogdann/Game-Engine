#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera(glm::vec3 _position, glm::vec3 axis[3], float _fov, float _near,
               float _far)
    : position(_position),
      fov(_fov),
      near(_near),
      far(_far) {
    this->orientation = glm::quat_cast(glm::mat3(axis[0], axis[1], axis[2]));
}

Camera::~Camera() {}

glm::vec3 Camera::getUp() {
    return glm::normalize(this->orientation * glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::getFront() {
    return glm::normalize(this->orientation * glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 Camera::getRight() {
    return glm::normalize(this->orientation * glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::move(glm::vec3 dir) { this->position += dir; }

void Camera::moveFront(float units) {
    this->position += units * this->getFront();
}

void Camera::moveUp(float units) { this->position += units * this->getUp(); }

void Camera::moveRight(float units) {
    this->position += units * this->getRight();
}

void Camera::rotate(glm::vec3 axis, float angle) {
    axis = glm::normalize(axis);
    float radians = glm::radians(angle);
    glm::quat q = glm::angleAxis(radians, axis);
    orientation = glm::normalize(q * orientation);
}

void Camera::rotateXY(float angleX, float angleY) {
    glm::quat qx = glm::angleAxis(glm::radians(angleX), glm::vec3(1, 0, 0));
    glm::quat qy = glm::angleAxis(glm::radians(angleY), glm::vec3(0, 1, 0));

    orientation = glm::normalize(qy * orientation * qx);
}

glm::mat4 Camera::getView() {
    return glm::lookAt(this->position, this->position + this->getFront(),
                       this->getUp());
}

glm::mat4 Camera::getProjection(float aspectRatio) {
    return glm::perspective(glm::radians(this->fov), aspectRatio, this->near,
                            this->far);
}

CameraHandler::CameraHandler(Window &window) {
    this->context = window.getContext();
    this->rotationSpeed = 1.0f;
    this->movementSpeed = 1.0f;
}

CameraHandler::CameraHandler(Window &window, float movementSpeed,
                             float rotationSpeed) {
    this->context = window.getContext();
    this->movementSpeed = movementSpeed;
    this->rotationSpeed = rotationSpeed;
}

CameraHandler::~CameraHandler() {}

void CameraHandler::setMovementSpeed(float speed) {
    this->movementSpeed = speed;
}

void CameraHandler::setRotationSpeed(float speed) {
    this->rotationSpeed = speed;
}

float CameraHandler::getMovementSpeed() { return this->movementSpeed; }

float CameraHandler::getRotationSpeed() { return this->rotationSpeed; }

void DefaultCameraHandler::initTable() {
    this->keyTable.insert({KEY_A, false});
    this->keyTable.insert({KEY_D, false});
    this->keyTable.insert({KEY_W, false});
    this->keyTable.insert({KEY_S, false});
}

DefaultCameraHandler::DefaultCameraHandler(Window &window)
    : CameraHandler(window) {
    initTable();
}

DefaultCameraHandler::DefaultCameraHandler(Window &window, float movementSpeed,
                                           float rotationSpeed)
    : CameraHandler(window, movementSpeed, rotationSpeed) {
    initTable();
}

DefaultCameraHandler::~DefaultCameraHandler() {}

void DefaultCameraHandler::handleEvent(Camera &camera, Event &event,
                                       float deltaTime) {

    if (event.motion.triggered) {
        if (this->firstCall) {
            this->firstCall = false;
            this->currentX = event.motion.x;
            this->currentY = event.motion.y;
            return;
        }

        double offsetX = event.motion.x - this->currentX;
        double offsetY = event.motion.y - this->currentY;
        double angleX = offsetX * rotationSpeed * deltaTime;
        double angleY = offsetY * rotationSpeed * deltaTime;
        this->currentX = event.motion.x;
        this->currentY = event.motion.y;
        camera.rotateXY(angleY, -angleX);
    }

    if (event.key.triggered) {
        auto it = keyTable.find(event.key.keysym.key);
        if (it != keyTable.end()) {
            if (event.key.action == KEY_PRESSED) {
                keyTable[event.key.keysym.key] = true;
            }
            if (event.key.action == KEY_RELEASED) {
                keyTable[event.key.keysym.key] = false;
            }
        }
    }

    if (keyTable[KEY_A]) {
        glm::vec3 offset = (movementSpeed * deltaTime) * camera.getRight();
        offset[1] = 0.0f;
        camera.position += offset;
    }
    if (keyTable[KEY_D]) {
        glm::vec3 offset = (movementSpeed * deltaTime) * camera.getRight();
        offset[1] = 0.0f;
        camera.position -= offset;
    }
    if (keyTable[KEY_W]) {
        glm::vec3 offset = (movementSpeed * deltaTime) * camera.getFront();
        offset[1] = 0.0f;
        camera.position += offset;
    }
    if (keyTable[KEY_S]) {
        glm::vec3 offset = (movementSpeed * deltaTime) * camera.getFront();
        offset[1] = 0.0f;
        camera.position -= offset;
    }
}
