#include "../../files/files.h"
#include "../../graphics/graphics.h"
#include "../../graphics/model/model.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

int main(void) {
    Program program;
    program.start();
    Window window("MyApp", 800, 800);
    program.useWindow(window);
    Event event;
    Renderer renderer;

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
    Camera camera(position, axis, fov, near, far);

    std::ifstream vertexFile("./shaders/vertex.glsl");
    std::ifstream fragmentFile("./shaders/fragment.glsl");
    Shader newShader(FileToString(vertexFile), FileToString(fragmentFile));

    Shader *shader = Shader::getCreator()->createShader(
        SIMPLE_SHADER, SHADER_COLOR, COORDINATES_XYZ);

    newShader.bind();

    Mesh *canvas =
        Surface::generateFlatSurface(800, 800, &newShader, SHADER_COLOR, true);
    Model::rotate(canvas, 7, {1.0f, 0.0f, 0.0f}, 90.0f);
    // Actor temp({0.0f, -10.0f, 50.0f}, {500.0f, 500.0f, 500.0f});

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float iTime = 0.0f;
    while (!window.isClosed()) {
        renderer.clear();
        window.clear();
        iTime = glfwGetTime();

        window.pollEvents(event);

        newShader.setUniform1f("iTime", iTime);
        newShader.setUniform1f("ar", Program_Settings::aspectRatio);
        renderer.draw(*canvas->getVertexArray(), newShader,
                      canvas->getVertexCount());
        // renderer.draw(temp, *canvas, camera);
        window.swap();
    }

    program.terminate();

    delete canvas;
    delete shader;
    return 0;
}
