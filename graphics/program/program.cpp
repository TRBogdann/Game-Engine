#include "program.h"
#include <iostream>

int Event::last_ID = 0;

Transformation_Mode Program_Settings::transformation_mode = Quaternion_Mode;
Cursor_Mode Program_Settings::cursor_mode = NORMAL;
bool Program_Settings::vSync = 0;
float Program_Settings::aspectRatio = 1.0f;
Projection_Style Program_Settings::proj_style = Perspective_Style;

Program::Program()
    : errorMessage(""),
      terminated(0),
      _window(0) {}

void Program::start() {
    if (glfwInit() != GLFW_TRUE) {
        this->errorMessage = "Could not initialize GLFW";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Program::useWindow(Window &window, bool useDepthFuntion) {
    _window = &window;
    glfwMakeContextCurrent(_window->getContext());
    if (glewInit() != GLEW_OK) {
        errorMessage = "GLEW initialization failed\n";
        return;
    }
    int width, height;
    glfwGetFramebufferSize(_window->getContext(), &width, &height);
    glViewport(0, 0, width, height);
    Program_Settings::aspectRatio =
        float(window.getHeight()) / float(window.getWidth());

    if (useDepthFuntion) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Program::terminate() {
    if (_window != nullptr) {
        if (!_window->wasDestroyed())
            _window->destroy();
    }
    if (!terminated) {
        glfwTerminate();
        terminated = 1;
    }
}

Program::~Program() {
    if (!terminated) {
        glfwTerminate();
    }
}

bool Program::CheckForError() {
    if (this->_window)
        if (this->_window->getErrorMessage() != "") {
            std::cout << this->_window->getErrorMessage();
            return 1;
        }

    if (this->errorMessage != "") {
        std::cout << this->errorMessage;
        return 1;
    }
    return 0;
}

void Program::setCursorMode(Cursor_Mode mode) {
    if (mode == HIDDEN) {
        glfwSetInputMode(this->_window->window, GLFW_CURSOR,
                         GLFW_CURSOR_HIDDEN);
        Program_Settings::cursor_mode = HIDDEN;
    }

    if (mode == NORMAL) {
        glfwSetInputMode(this->_window->window, GLFW_CURSOR,
                         GLFW_CURSOR_NORMAL);
        Program_Settings::cursor_mode = NORMAL;
    }

    if (mode == DISABLED) {
        glfwSetInputMode(this->_window->window, GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED);
        Program_Settings::cursor_mode = DISABLED;
    }

    if (mode == DISABLED_RAW) {
        glfwSetInputMode(this->_window->window, GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED);
        glfwSetInputMode(this->_window->window, GLFW_RAW_MOUSE_MOTION,
                         GLFW_TRUE);
        Program_Settings::cursor_mode = DISABLED_RAW;
    }
}
