#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../../../src/graphics/shaders/shaders.h"
#include "../../../src/graphics/window/window.h"
#include "../../../src/graphics/camera/camera.h"

class Toolbar
{
    public:
    Toolbar(Window* window,Shader* shader);
    ~Toolbar();

    void render(Camera& camera,float deltatime);

    private:
    Window* window;
    Shader* shader;
    float lightSource[3] = {0.0f,100.0f,-40.0f};
    float ambientColor[3] = {1.0,1.0,1.0};
    float teapotColor[3] = {1.0,1.0,1.0f};
    float ambient = 0.5f;
    float specular = 0.5f;
    float FPS;
    float innerTime;
};