#pragma once
#include <GameEngine/Events/events.h>
#include <GameEngine/Graphics/macros.h>
#include <GameEngine/Graphics/window.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <map>

class Camera {
    public:
        Camera(glm::vec3 _position, glm::vec3 axis[3], float _fov, float _near,
               float _far);
        ~Camera();

        void move(glm::vec3 dir);
        void moveRight(float units);
        void moveUp(float units);
        void moveFront(float units);
        void rotate(glm::vec3 axis, float angle);
        void rotateXY(float angleX, float angleY);
        glm::vec3 getFront();
        glm::vec3 getUp();
        glm::vec3 getRight();

        glm::mat4 getView();
        glm::mat4 getProjection(float aspectRatio);
        glm::vec3 position;
        glm::quat orientation;
        float fov;
        float near;
        float far;

        friend class CameraHandler;

    private:
};

class CameraHandler {
    public:
        CameraHandler(Window &window);
        CameraHandler(Window &window, float movementSpeed, float rotationSpeed);
        ~CameraHandler();
        virtual void handleEvent(Camera &camera, Event &event,
                                 float deltaTime) = 0;
        float getRotationSpeed();
        float getMovementSpeed();
        void setMovementSpeed(float speed);
        void setRotationSpeed(float speed);

    protected:
        GLFWwindow *context;
        float rotationSpeed;
        float movementSpeed;
};

class DefaultCameraHandler : public CameraHandler {
    public:
        DefaultCameraHandler(Window &window);
        DefaultCameraHandler(Window &window, float movementSpeed,
                             float rotationSpeed);
        ~DefaultCameraHandler();
        void handleEvent(Camera &camera, Event &event, float deltaTime);

    private:
        void initTable();
        bool firstCall = true;
        double currentX = 0.0f, currentY = 0.0f;
        std::map<unsigned char, bool> keyTable;
};
