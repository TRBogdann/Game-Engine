#include "tools.h"
#include <imgui.h>

Toolbar::Toolbar(Window* window,Shader* shader):window(window),shader(shader)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window->getContext(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    window->setColor(ambient/2*255, ambient/2*255, ambient/2*255, 255);

    shader->bind();
    shader->setUniform3f("aColor", teapotColor[0], teapotColor[1], teapotColor[2]);
    shader->setUniform1f("ambient", ambient);
    shader->setUniform3f("lightPos", 
        lightSource[0], 
        lightSource[1], 
        lightSource[2]
    );
    shader->setUniform1f("specularStrength",specular);
    shader->setUniform3f("lightColor", 
        ambientColor[0], 
        ambientColor[1], 
        ambientColor[2]
    );
}

Toolbar::~Toolbar()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Toolbar::render(Camera& camera, float deltatime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    shader->setUniform3f("viewPos", 
            camera.position.x,
            camera.position.y, 
            camera.position.z
    );

    this->innerTime += deltatime;
    if (innerTime > 1.0f) {
        FPS = 1.0f / deltatime;
        innerTime = 0.0f;
    }
    ImGui::Begin("Tools");
    ImGui::Text("FPS: %.1f", FPS);
    ImGui::Text("Press r to change the rotation");
    ImGui::Text("Press s to stop the rotation");

    if(ImGui::SliderFloat3("Teapot Color", this->teapotColor, 0.0f, 1.0f))
    {
        shader->setUniform3f("aColor", teapotColor[0], teapotColor[1], teapotColor[2]);
    }

    if(ImGui::SliderFloat3("Light Position",this->lightSource,-400.0f,400.0f))
    {
        shader->setUniform3f("lightPos", 
            lightSource[0], 
            lightSource[1], 
            lightSource[2]
        );
    }

    if(ImGui::SliderFloat3("Light Color", this->ambientColor, 0.0f, 1.0f))
    {
        window->setColor(
            ambientColor[0]*ambient/2*255, 
            ambientColor[1]*ambient/2*255, 
            ambientColor[2]*ambient/2*255, 
            255
        );
        shader->setUniform3f("lightColor", 
            ambientColor[0], 
            ambientColor[1], 
            ambientColor[2]
        );
    };

    if(ImGui::SliderFloat("Ambient",&this->ambient,0.0f,2.0f))
    {
        window->setColor(
            ambientColor[0]*ambient/2*255, 
            ambientColor[1]*ambient/2*255, 
            ambientColor[2]*ambient/2*255, 
            255
        );
        shader->setUniform1f("ambient", ambient);
    };

    if(ImGui::SliderFloat("Specular", &this->specular, 0.0f,50.0f))
    {
        shader->setUniform1f("specularStrength",specular);
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}