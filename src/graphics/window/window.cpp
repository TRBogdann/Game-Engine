#include "window.h"
#include "../settings.h"
#include <GLFW/glfw3.h>

void window_fbsize_callback(GLFWwindow *window, int width, int height) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->window.triggered = true;
    event->window.action = WINDOW_RESIZED;
    event->window.data1 = width;
    event->window.data2 = height;
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->key.triggered = true;
    event->key.action = action;
    event->key.keysym.scancode = scancode;
    event->key.keysym.key = key;
    event->key.keysym.mods = mods;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->motion.triggered = true;
    event->motion.action = MOUSE_MOTION;
    event->motion.x = xpos;
    event->motion.y = ypos;
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->button.triggered = true;
    event->button.action = action;
    event->button.button = button;
    event->button.state = mods;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->wheel.triggered = true;
    event->wheel.action = WHEEL_SCROLL;
    event->wheel.x = xoffset;
    event->wheel.y = yoffset;
}

void window_close_callback(GLFWwindow *window) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    event->triggered = true;
    event->window.triggered = true;
    event->window.action = WINDOW_CLOSED;
}

void window_maximize_callback(GLFWwindow *window, int maximized) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->window.triggered = true;
    glfwGetWindowSize(window, &event->window.data1, &event->window.data2);
    if (maximized) {
        event->window.action = WINDOW_MAXIMIZED;
    } else {
        event->window.action = WINDOW_RESTORED;
    }
}

void window_iconify_callback(GLFWwindow *window, int iconified) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->window.triggered = true;
    glfwGetWindowSize(window, &event->window.data1, &event->window.data2);
    if (iconified) {
        event->window.action = WINDOW_MINIMIZED;
    } else {
        event->window.action = WINDOW_RESTORED;
    }
}
void window_focus_callback(GLFWwindow *window, int focused) {
    Event *event = (Event *)glfwGetWindowUserPointer(window);
    event->triggered = true;
    event->window.triggered = true;
    if (focused) {
        event->window.action = WINDOW_FOCUSED;
    } else {
        event->window.action = WINDOW_NOT_FOCUSED;
    }
}

Window::Window(const std::string &title, int width, int height)
    : _title(title),
      _width(width),
      _height(height),
      _closed(0),
      _r(0.0f),
      _g(0.0f),
      _b(0.0f),
      _a(0.0f),
      errorMessage(""),
      type(0),
      _resizable(1) {
    window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    if (window == NULL) {
        errorMessage = "Window Creation Failed";
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetWindowMaximizeCallback(window, window_maximize_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetFramebufferSizeCallback(window, window_fbsize_callback);
}

Window::~Window() {
    if (!destroyed)
        glfwDestroyWindow(this->window);
}

bool Window::isClosed() { return _closed; }

int Window::getHeight() { return this->_height; }

int Window::getWidth() { return this->_width; }

void Window::clear() {
    glClearColor(_r, _g, _b, _a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::swap() { glfwSwapBuffers(window); };

void Window::setColor(unsigned char r, unsigned char g, unsigned char b,
                      unsigned char alpha) {
    this->_r = float(r) * 100.0f / 25500.0f;
    this->_g = float(g) * 100.0f / 25500.0f;
    this->_b = float(b) * 100.0f / 25500.0f;
    this->_a = float(alpha) * 100.0f / 25500.0f;
}

void Window::destroy() {
    _closed = 1;
    destroyed = 1;
    glfwDestroyWindow(this->window);
}

GLFWwindow *Window::getContext() { return this->window; }

bool Window::wasDestroyed() { return destroyed; }

std::string Window::getErrorMessage() { return this->errorMessage; }

void Window::pollEvents(Event &event) {

    if (event_ID != event.event_ID) {
        this->event_ID = event.event_ID;
        glfwSetWindowUserPointer(window, &event);
    }

    event.triggered = false;
    event.window.triggered = false;
    event.key.triggered = false;
    event.motion.triggered = false;
    event.button.triggered = false;
    event.wheel.triggered = false;
    glfwPollEvents();

    if (event.triggered) {
        if (event.window.triggered) {
            if (event.window.action == WINDOW_RESIZED) {
                this->_height = event.window.data1;
                this->_width = event.window.data2;
                Program_Settings::aspectRatio =
                    float(this->_height) / float(this->_width);
            }
            if (event.window.action == WINDOW_CLOSED) {
                this->_closed = 1;
            }
            if (event.window.action == WINDOW_RESTORED) {
                this->_height = event.window.data1;
                this->_width = event.window.data2;
                Program_Settings::aspectRatio =
                    float(this->_height) / float(this->_width);
            }
            if (event.window.action == WINDOW_MAXIMIZED) {
                this->_height = event.window.data1;
                this->_width = event.window.data2;
                Program_Settings::aspectRatio =
                    float(this->_height) / float(this->_width);
            }
        }
    }
}
