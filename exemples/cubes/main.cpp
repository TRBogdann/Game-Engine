#include "../../graphics/graphics.h"
#include <iostream>

int main(void) {
    Program program;
    program.start();
    Window window("MyApp", 800, 800);
    program.useWindow(window);
    Event event;
    Renderer render;

    if (program.CheckForError())
        return 1;

    program.setCursorMode(DISABLED_RAW);
    window.setColor(100, 255, 255, 255);

    float fov = 90;
    float far = 1000.0f;
    float near = 5.0f;
    glm::vec3 position(0.0f, 0.0f, 0.0f);
    glm::vec3 axis[3] = {glm::vec3(1.0f, 0.0f, 0.0f),
                         glm::vec3(0.0f, 1.0f, 0.0f),
                         glm::vec3(0.0f, 0.0f, 1.0f)};

    Texture textures[11] = {Texture("../textures/dirt.png", 0, 1),
                            Texture("../textures/grass.png", 0, 1),
                            Texture("../textures/wood.png", 0, 1),
                            Texture("../textures/wall.jpg", 0, 0),
                            Texture("../textures/crate.png", 0, 1),
                            Texture("../textures/crate.jpg", 0, 0),
                            Texture("../textures/doomwall.jpg", 0, 0),
                            Texture("../textures/grass2.png", 0, 1),
                            Texture("../textures/log1.png", 0, 1),
                            Texture("../textures/rockwall.jpg", 0, 0),
                            Texture("../textures/roof.jpg", 0, 0)};

    Camera camera(position, axis, fov, near, far);
    CameraHandler *cameraHandler =
        new DefaultCameraHandler(window, 200.0f, 5.0f);

    // House Fance and Cubes
    ShapeRegistry *shapeRegistry = ShapeRegistry::getInstance();
    Mesh *textured_cube =
        shapeRegistry->getShape(SHAPE_CUBE, SHADER_TEXTURE, MVP_SHADER);

    Actor cubes[11] = {
        Actor(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(15.0f, 0.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(30.0f, 0.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(45.0f, 0.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(0.0f, 15.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(15.0f, 15.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(30.0f, 15.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(45.0f, 15.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(0.0f, 30.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(15.0f, 30.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
        Actor(glm::vec3(30.0f, 30.0f, 40.0f), glm::vec3(10.0f, 10.0f, 10.0f)),
    };

    if (!textured_cube) {
        std::cout << "Mesh could not be loaded";
        return 1;
    }

    float rot = 0.0f;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!window.isClosed()) {
        render.clear();
        window.clear();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.pollEvents(event);
        cameraHandler->handleEvent(camera, event, deltaTime);

        rot += 0.05f;

        for (int i = 0; i < 11; i++) {
            textures[i].bind();
            cubes[i].setRotation(glm::vec3(0.0f, rot, 0.0f));
            render.draw(cubes[i], *textured_cube, camera);
        }

        window.swap();
    }

    program.terminate();

    delete textured_cube;
    delete shapeRegistry;
    delete (DefaultCameraHandler *)cameraHandler;
    return 0;
}
