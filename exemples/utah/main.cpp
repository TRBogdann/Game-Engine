#include "../../src/files/files.h"
#include "tools/tools.h"
#include "event_handler/handler.h"
#include "../../src/graphics/graphics.h"




int main(void) {
    Program program;
    program.start();
    Window window("Utah Teapot", 800, 800);
    program.useWindow(window);
    Event event;
    Renderer renderer;

    if (program.CheckForError())
        return 1;
    program.setMultisampling(4);

    float fov = 45.0f;
    float far = 1000.0f;
    float near = 10.0f;
    glm::vec3 position(0.0f, 0.0f, 0.0f);
    glm::vec3 axis[3] = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    };
    Camera camera(position, axis, fov, near, far);


    std::ifstream vertexShader("./shaders/vertex.glsl");
    std::ifstream fragmentShader("./shaders/fragment.glsl");

    Shader objectShader(FileToString(vertexShader),FileToString(fragmentShader));
    Toolbar toolbar(&window,&objectShader);
    Mesh* teapotMesh = Blender::loadWavefront("./utah.obj",&objectShader); 
    Actor teapot({0.0f,-7.5f,40.0f},{1.0f,1.0f,1.0f});

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!window.isClosed()) {
        renderer.clear();
        window.clear();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    
        window.pollEvents(event);
        handleEvents(event, teapot, deltaTime);

        toolbar.render(camera, deltaTime);
        renderer.draw(teapot,*teapotMesh,camera);

        window.swap();
    }

    program.terminate();
    return 0;
}
