#include "../../src/graphics/graphics.h"

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

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
    window.setColor(200, 255, 255, 255);

    float fov = 45.0f;
    float far = 2000.0f;
    float near = 10.0f;
    glm::vec3 position(0.0f, 80.0f, 0.0f);
    glm::vec3 axis[3] = {glm::vec3(1.0f, 0.0f, 0.0f),
                         glm::vec3(0.0f, 1.0f, 0.0f),
                         glm::vec3(0.0f, 0.0f, 1.0f)};

    int textureIndex = 0;
    Texture textures[11] = {Texture("../textures/dirt.png", 0, 1),
                            Texture("../textures/grass.png", 0, 1),
                            Texture("../textures/wood.png", 0, 1),
                            Texture("../textures/wall.jpg", 0, 0),
                            Texture("../textures/crate.png", 0, 1),
                            Texture("../textures/crate.jpg", 0, 0),
                            Texture("../textures/doomwall.jpg", 0, 0),
                            Texture("../textures/grass2.png", 0, 1),
                            Texture("../textures/housewall.png", 0, 1),
                            Texture("../textures/rockwall.jpg", 0, 0),
                            Texture("../textures/roof.jpg", 0, 0)};

    Camera camera(position, axis, fov, near, far);
    CameraHandler *cameraHandler =
        new DefaultCameraHandler(window, 200.0f, 5.0f);
    // House Fance and Cubes
    ShapeRegistry *shapeRegistry = ShapeRegistry::getInstance();
    Mesh *textured_cube =
        shapeRegistry->getShape(SHAPE_CUBE, SHADER_TEXTURE, MVP_SHADER);
    
    std::cout<<textured_cube->getVertexCount();
        Actor house[8] = {
        Actor({-50.0f, 100.0f, 600.0f}, {280.0f, 200.0f, 20.0f}),
        Actor({100.0f, 100.0f, 500.0f}, {20.0f, 200.0f, 220.0f}),
        Actor({-200.0f, 100.0f, 500.0f}, {20.0f, 200.0f, 220.0f}),
        Actor({-140.0f, 33.3333f, 400.0f}, {100.0f, 66.6666f, 20.0f}),
        Actor({40.0f, 33.3333f, 400.0f}, {100.0f, 66.6666f, 20.0f}),
        Actor({-50.0f, 166.6f, 400.0f}, {280.0f, 66.6666f, 20.0f}),
        Actor({-105.0f, 100.0f, 400.0f}, {30.0f, 66.6666f, 20.0f}),
        Actor({5.0f, 100.0f, 400.0f}, {30.0f, 66.6666f, 20.0f})};

    // Terrain
    Shader *terrainShader = Shader::getCreator()->createShader(
        MVP_SHADER, SHADER_TEXTURE, COORDINATES_XYZ);
    Mesh *flatSurface =
        Surface::generateFlatSurface(10, 10, terrainShader, SHADER_TEXTURE);
    Actor terrain(glm::vec3(0.0f, 0.0f, -300.0f),
                  glm::vec3(1000.0f, 1000.0f, 300.0f));

    Actor land({0.0f, 0.0f, 700.0f}, {1000.f, 1000.0f, 700.0f});
    textures[textureIndex].bind();

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

        textures[textureIndex + 1].bind();
        render.draw(terrain, *flatSurface, camera);

        textures[textureIndex].bind();
        render.draw(land, *flatSurface, camera);
        textures[8].bind();

        for (int i = 0; i < 8; i++) {
            render.draw(house[i], *textured_cube, camera);
        }
        window.swap();
    }

    program.terminate();

    delete flatSurface;
    delete terrainShader;
    delete textured_cube;
    delete shapeRegistry;
    delete (DefaultCameraHandler *)cameraHandler;

    return 0;
}
