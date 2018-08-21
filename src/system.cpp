#include <system.hpp>
#include <stdexcept>
#include <iostream>
#include <iomanip>

std::string RESOURCE_PATH = "resources/";

void WindowManager::glfwErrorCallback(int error_code, const char *error_message) {
    std::cerr << "Error thrown by GLFW. Error code: " << std::hex << error_code
              << std::endl;
    std::cerr << "Error message: '" << error_message << '\'';
}

void WindowManager::initGLFW() {
    int success = glfwInit();
    glfwSetErrorCallback(glfwErrorCallback);
    if(success != GLFW_TRUE)
        throw std::runtime_error ("Error initializing GLFW");
}

void WindowManager::createWindow(const std::string &title, int width, int height) {
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(NULL == window)
        throw std::runtime_error ("Error creating a GLFW window");
    glfwMakeContextCurrent(window);
}

void WindowManager::setDefaultState() {
    glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 1.0f);
    glfwSwapInterval(1);
}

void WindowManager::initGLEW() {
    GLenum error_code;
    glewExperimental = true;
    error_code = glewInit();
    if(GLEW_OK != error_code)
        throw std::runtime_error (std::string("Error thrown by GLEW: ") +
                                  (char*)glewGetErrorString(error_code));
}

WindowManager::WindowManager(const std::string &title, int width, int height) {
    window = nullptr;
    initGLFW();
    createWindow(title.c_str(), width, height);
    setDefaultState();
    initGLEW();
}

bool WindowManager::endFlag() {
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

void WindowManager::initNewFotogram() {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
}

void WindowManager::endFotogram() {
    glfwSwapBuffers(window);
}

WindowManager::~WindowManager() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
