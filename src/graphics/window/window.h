#pragma once
#include "../../events/events.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

// Alte optiuni

// Full screen
// GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

// Borderless
/*
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

glfwWindowHint(GLFW_RED_BITS, mode->redBits);
glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title",
monitor, NULL);
 */

class Window {
    public:
        Window(const std::string &title, int width, int height);
        ~Window();
        int getHeight();
        int getWidth();
        void Close();
        bool isClosed();
        void setColor(unsigned char r, unsigned char g, unsigned char b,
                      unsigned char alpha);
        void destroy();
        void clear();
        void swap();
        bool wasDestroyed();
        void pollEvents(Event &event);
        // void setIcon(std::string path); TODO

        GLFWwindow *getContext();
        std::string getErrorMessage();

        friend class Program;

    private:
        int event_ID = -1;
        bool _resizable;
        GLFWwindow *window;
        bool _closed;
        int type;
        int _width;
        int _height;
        std::string errorMessage;
        std::string _title;

        float _r, _g, _b, _a;
        bool destroyed = 0;
};
