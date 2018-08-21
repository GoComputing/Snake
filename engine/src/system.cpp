#include <system.hpp>
#include <shader.hpp>
#include <stdexcept>
#include <iostream>
#include <iomanip>

std::string RESOURCE_PATH = "resources/";

static constexpr int OPENGL_VERSION_MAJOR = 3;  // Default OpenGL context version major
static constexpr int OPENGL_VERSION_MINOR = 3;  // Default OpenGL context version minor
static constexpr float BACKGROUND_R = 0.2f;     // Default background color (red)
static constexpr float BACKGROUND_G = 0.2f;     // Default background color (green)
static constexpr float BACKGROUND_B = 0.7f;     // Default background color (blue)
static unsigned int num_frames;
static GLdouble last_time;
static GLdouble last_framerate;
static GLdouble framerate_update_interval;
static GLFWwindow *window;                      // Window managed by GLFW
static GLint window_size_x;
static GLint window_size_y;

static void glfwErrorCallback(int error_code, const char *error_message) {
    std::cerr << "Error thrown by GLFW. Error code: " << std::hex << error_code
              << std::endl;
    std::cerr << "Error message: '" << error_message << '\'';
}

static void glfwWindowSizeCallback(GLFWwindow */*window*/, int x, int y) {
    window_size_x = x;
    window_size_y = y;
    Shader::setWindowRatio(WindowManager::getRatio());
    glViewport(0, 0, window_size_x, window_size_y);
}

static void initGLFW() {
    int success = glfwInit();
    glfwSetErrorCallback(glfwErrorCallback);
    if(success != GLFW_TRUE)
        throw std::runtime_error ("Error initializing GLFW");
}

static void createGLFW_Window(const std::string &title, int width, int height) {
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(NULL == window)
        throw std::runtime_error ("Error creating a GLFW window");
    glfwMakeContextCurrent(window);
}

static void setDefaultState() {
    glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 1.0f);
    glfwSwapInterval(1);
}

static void setGLFW_Callbacks() {
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
}

static void initGLEW() {
    GLenum error_code;
    glewExperimental = true;
    error_code = glewInit();
    if(GLEW_OK != error_code)
        throw std::runtime_error (std::string("Error thrown by GLEW: ") +
                                  (char*)glewGetErrorString(error_code));
}

void WindowManager::create(const std::string &title, int width, int height) {
    window = nullptr;
    
    initGLFW();
    createGLFW_Window(title.c_str(), width, height);
    setDefaultState();
    initGLEW();
    setGLFW_Callbacks();
    
    last_time = glfwGetTime();
    num_frames = 0;
    last_framerate = 0.0;
    framerate_update_interval = 0.5f;
    window_size_x = width;
    window_size_y = height;
}

bool WindowManager::endFlag() {
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

void WindowManager::initNewFotogram() {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
}

void WindowManager::endFotogram() {
    GLdouble current_time;
    glfwSwapBuffers(window);
    ++num_frames;
    current_time = glfwGetTime();
    if(current_time-last_time >= framerate_update_interval) {
        last_framerate = num_frames / (current_time-last_time);
        num_frames = 0;
        last_time = current_time;
    }
}

GLfloat WindowManager::getFramerate() {
    return last_framerate;
}

void WindowManager::getSize(int &x, int &y) {
    x = window_size_x;
    y = window_size_y;
}

GLfloat WindowManager::getRatio() {
    int x, y;
    getSize(x, y);
    return (GLfloat)x / (GLfloat)y;
}

bool WindowManager::keyPressed(int key) {
    return glfwGetKey(window, key) != GLFW_RELEASE;
}

void WindowManager::destroy() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
