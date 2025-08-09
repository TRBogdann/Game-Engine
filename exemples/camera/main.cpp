#include "../../graphics/buffers/buffers.h"
#include "../../graphics/camera/camera.h"
#include "../../graphics/program/program.h"
#include "../../graphics/renderer/renderer.h"
#include "../../graphics/shaders/shaders.h"
#include "../../graphics/transformations/transformations.h"
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

int main(void) {

    float colors[] = {
        0.583f, 0.771f, 0.014f, 0.609f, 0.115f, 0.436f, 0.327f, 0.483f, 0.844f,
        0.822f, 0.569f, 0.201f, 0.435f, 0.602f, 0.223f, 0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f, 0.559f, 0.436f, 0.730f, 0.359f, 0.583f, 0.152f,
        0.483f, 0.596f, 0.789f, 0.559f, 0.861f, 0.639f, 0.195f, 0.548f, 0.859f,
        0.014f, 0.184f, 0.576f, 0.771f, 0.328f, 0.970f, 0.406f, 0.615f, 0.116f,
        0.676f, 0.977f, 0.133f, 0.971f, 0.572f, 0.833f, 0.140f, 0.616f, 0.489f,
        0.997f, 0.513f, 0.064f, 0.945f, 0.719f, 0.592f, 0.543f, 0.021f, 0.978f,
        0.279f, 0.317f, 0.505f, 0.167f, 0.620f, 0.077f, 0.347f, 0.857f, 0.137f,
        0.055f, 0.953f, 0.042f, 0.714f, 0.505f, 0.345f, 0.783f, 0.290f, 0.734f,
        0.722f, 0.645f, 0.174f, 0.302f, 0.455f, 0.848f, 0.225f, 0.587f, 0.040f,
        0.517f, 0.713f, 0.338f, 0.053f, 0.959f, 0.120f, 0.393f, 0.621f, 0.362f,
        0.673f, 0.211f, 0.457f, 0.820f, 0.883f, 0.371f, 0.982f, 0.099f, 0.879f};

    float data[252] = {
        -1.0f, -1.0f, -1.0f, 1.0,   0.0f,  0.0f,  1.0f, // triangle 1 : begin
        -1.0f, -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  1.0f,
        1.0,   0.0f,  0.0f,  1.0f,                      // triangle 1 : end
        1.0f,  1.0f,  -1.0f, 1.0,   0.0f,  0.0f,  1.0f, // triangle 2 : begin
        -1.0f, -1.0f, -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,
        1.0,   0.0f,  0.0f,  1.0f, // triangle 2 : end
        1.0f,  -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f,  -1.0f, -1.0f, -1.0f,
        1.0,   0.0f,  0.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0,   0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  1.0f,  -1.0f,
        -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  -1.0f, -1.0f, -1.0f, 1.0,   0.0f,
        0.0f,  1.0f,  -1.0f, -1.0f, -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  -1.0f,
        1.0f,  1.0f,  1.0,   0.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0,
        0.0f,  0.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f,  -1.0f, -1.0f, -1.0f,
        1.0,   0.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0,   0.0f,  0.0f,
        1.0f,  -1.0f, -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f,  1.0f,  -1.0f,
        1.0f,  1.0,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0,   0.0f,
        0.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  1.0f,
        1.0f,  -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0,
        0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0,   0.0f,  0.0f,  1.0f,
        1.0f,  -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        1.0,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0,   0.0f,  0.0f,
        1.0f,  -1.0f, 1.0f,  -1.0f, 1.0,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        1.0f,  1.0,   0.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0,   0.0f,
        0.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0,   0.0f,  0.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0,   0.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0,
        0.0f,  0.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0,   0.0f,  0.0f,  1.0f};

    // Adding the right colors to the data buffer
    for (int i = 0; i < 36; i++) {
        data[i * 7 + 3] = colors[i * 3];
        data[i * 7 + 4] = colors[i * 3 + 1];
        data[i * 7 + 5] = colors[i * 3 + 2];
    }

    Program program;
    program.start();
    Window window("MyApp", 800, 800);
    program.useWindow(window);
    Renderer renderer;
    Event event;

    if (program.CheckForError())
        return 1;

    program.setCursorMode(DISABLED_RAW);
    window.setColor(0, 100, 100, 255);

    // Camera Init
    float fov = 90;
    float far = 1000.0f;
    float near = 5.0f;
    glm::vec3 position(0.0f, 0.0f, 0.0f);
    glm::vec3 axis[3] = {glm::vec3(1.0f, 0.0f, 0.0f),
                         glm::vec3(0.0f, 1.0f, 0.0f),
                         glm::vec3(0.0f, 0.0f, 1.0f)};

    Camera camera(position, axis, fov, near, far);
    CameraHandler *handler = new DefaultCameraHandler(window, 200.0f, 5.0f);
    // Shader Init
    GraphicalAtribute *atributes =
        GraphicalAtribute::getCreator()->createAtributes(SHADER_COLOR,
                                                         COORDINATES_XYZ);
    int nOfAtributes = GraphicalAtribute::getCreator()->getNOfAtributes();
    Shader *shader = Shader::getCreator()->createShader(
        MVP_SHADER, SHADER_COLOR, COORDINATES_XYZ);

    if (!atributes) {
        std::cout << "Invalid createAtributes options\n";
        return 1;
    }

    if (!shader) {
        std::cout << "Invalid createShader options\n";
        return 1;
    }

    // Cube positions and MVP
    glm::vec3 cubePosition(0.0f, 0.0f, 40.0f);
    glm::vec3 cubeScale(10.0f, 10.0f, 10.0f);
    float angle = 0.0f;

    // Cube Buffers
    VertexArray arr(7 * sizeof(float));
    arr.bind();
    VertexBuffer buff(data, sizeof(data));
    arr.addData(buff, atributes, nOfAtributes);
    int vertexCount = sizeof(data) / 7;

    // Shader Binding
    shader->bind();

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!window.isClosed()) {
        renderer.clear();
        window.clear();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.pollEvents(event);
        handler->handleEvent(camera, event, deltaTime);

        angle += 0.01f;
        glm::mat4 rotation = Transform::rotation(glm::vec3(angle, 0.0f, 0.0f));
        glm::mat4 model =
            glm::translate(glm::mat4(1.0f), cubePosition) * rotation;
        model = glm::scale(model, cubeScale);
        glm::mat4 view = camera.getView();
        glm::mat4 projection =
            camera.getProjection(Program_Settings::aspectRatio);

        shader->setUniformMat4("model", model);
        shader->setUniformMat4("view", view);
        shader->setUniformMat4("projection", projection);

        renderer.draw(arr, *shader, vertexCount);

        window.swap();
    }

    program.terminate();

    delete[] atributes;
    delete shader;
    delete (DefaultCameraHandler *)handler;
    return 0;
}
