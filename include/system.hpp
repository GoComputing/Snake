#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern std::string RESOURCE_PATH;

class WindowManager {
private:
    static constexpr int OPENGL_VERSION_MAJOR = 3;  // Default OpenGL context version major
    static constexpr int OPENGL_VERSION_MINOR = 3;  // Default OpenGL context version minor
    static constexpr float BACKGROUND_R = 0.2f;     // Default background color (red)
    static constexpr float BACKGROUND_G = 0.2f;     // Default background color (green)
    static constexpr float BACKGROUND_B = 0.7f;     // Default background color (blue)
    GLFWwindow *window;                         // Window managed by GLFW
    
    static void glfwErrorCallback(int error_code, const char *error_message);
    
protected:
    void initGLFW();
    void createWindow(const std::string &title, int width, int height);
    void setDefaultState();
    void initGLEW();
    
public:
    WindowManager(const std::string &title, int width, int height);
    
    bool endFlag();
    void initNewFotogram();
    void endFotogram();
    
    ~WindowManager();
};

#endif
