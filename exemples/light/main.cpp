#include "../../src/files/files.h"
#include "../../src/graphics/graphics.h"
#include "../../src/string-utils/string_utils.h"
#include "./light-source/light_source.h"
#include <fstream>

int main(void) {
    Program program;
    program.start();
    Window window("Light Test", 800, 800);
    program.useWindow(window);
    Event event;
    Renderer renderer;

    if (program.CheckForError())
        return 1;

    window.setColor(135, 206, 235, 255);
    program.setCursorMode(Cursor_Mode::DISABLED_RAW);
    program.setMultisampling(4);

    float fov = 45.0f;
    float far = 1000.0f;
    float near = 10.0f;
    glm::vec3 position(0.0f, -15.0f, 0.0f);
    glm::vec3 axis[3] = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    };
    Camera camera(position, axis, fov, near, far);
    CameraHandler *cameraHandler = new DefaultCameraHandler(
        window,
        200.0f,
        5.0f
    );

    std::ifstream shaderFiles[] = {
        std::ifstream("./shaders/fragment.glsl"),
        std::ifstream("./shaders/light_source/vertex.glsl"),
        std::ifstream("./shaders/surface/vertex.glsl"),
        std::ifstream("./shaders/objects/vertex.glsl")};
    
    
    Shader lightShader(FileToString(shaderFiles[1]),
                    FileToString(shaderFiles[0]));
    
    shaderFiles[0].clear();
    shaderFiles[0].seekg(0);
    Shader surfaceShader(FileToString(shaderFiles[2]),
                        FileToString(shaderFiles[0]));
    
    shaderFiles[0].clear();
    shaderFiles[0].seekg(0);
    Shader objectShader(FileToString(shaderFiles[3]),
                        FileToString(shaderFiles[0]));


    LightSource lightSource(
        "./resource/sphere.obj",
        &lightShader,
        {0.0f,100.0f,100.f},
        {10.0f,10.0f,10.0f}
    );
    Mesh* surface = Surface::generateFlatSurface(500, 500, &surfaceShader, SHADER_COLOR);
    Mesh *skullMesh = Blender::loadWavefront("./resource/skull.obj", &objectShader);
    Mesh *shelfMesh = Blender::loadWavefront("./resource/shelf.obj", &objectShader);


    Actor shelf({0.0f, -80.0f, 0.0f}, {2.0f, 2.0f, 2.0f});
    Actor skull({0.0f, -25.5f, 20.0f}, {50.0f, 50.0f, 50.0f});
    Actor floor({0.0f, -80.0f, 0.0f}, {500.0f, 500.0f, 500.0f});


    surfaceShader.bind();
    surfaceShader.setUniform1f("ambient", LightSource::ambient);
    surfaceShader.setUniform3f("lightPos", 
        lightSource.position().x, 
        lightSource.position().y, 
        lightSource.position().z);
    

    objectShader.bind();
    objectShader.setUniform1f("ambient", LightSource::ambient);
    objectShader.setUniform3f("lightPos", 
        lightSource.position().x, 
        lightSource.position().y, 
        lightSource.position().z);
    objectShader.setUniform1f("specularStrength",LightSource::specularStrength);


    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!window.isClosed()) {
        renderer.clear();
        window.clear();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.pollEvents(event);
        cameraHandler->handleEvent(camera, event, deltaTime);

        lightSource.draw(renderer, camera);
        renderer.draw(floor, *surface, camera);

        renderer.draw(skull, *skullMesh, camera);
        objectShader.setUniform3f("aColor", 0.7, 0.0, 0.0);
        renderer.draw(shelf, *shelfMesh, camera);
        objectShader.setUniform3f("viewPos", camera.position.x,
                                  camera.position.y, camera.position.z);
        objectShader.setUniform3f("aColor", 0.7, 0.7, 0.7);
        window.swap();
    }

    program.terminate();
    return 0;
}
