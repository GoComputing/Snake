#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern std::string RESOURCE_PATH;

namespace WindowManager {
    void create(const std::string &title, int width, int height);
    
    bool endFlag();
    void initNewFotogram();
    void endFotogram();
    
    GLfloat getFramerate();
    void getSize(int &x, int &y);
    GLfloat getRatio();
    bool keyPressed(int key);
    
    void destroy();
}

#endif
