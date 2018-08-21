#include <motor.hpp>
#include <stdexcept>
#include <iostream>
#include <cmath>

int main() {
    try {
        WindowManager::create("Snake", 800, 600);
        Shader shader;
        Model square;
        GLfloat x;
        GLfloat y;
        
        shader.create(RESOURCE_PATH+"shaders/default.vs", RESOURCE_PATH+"shaders/default.fs");
        loadSquare(-0.5f, -0.5f, 1.0f, square);
        Shader::setWindowRatio(WindowManager::getRatio());
        
        while(!WindowManager::endFlag()) {
            WindowManager::initNewFotogram();
            
            x = 0.5f*std::cos(glfwGetTime());
            y = 0.5f*std::sin(glfwGetTime());
            shader.setUniformVector("position", GL_FLOAT, 2, x, y);
            square.render(shader);
            
            WindowManager::endFotogram();
        }
    } catch(const std::runtime_error &e) {
        std::cerr << "Fatal error: " << std::endl;
        std::cerr << e.what() << std::endl;
    }
    
    WindowManager::destroy();
    return 0;
}
