#include <motor.hpp>
#include <snake.hpp>
#include <stdexcept>
#include <iostream>
#include <cmath>

void drawBoard(const Snake &board, const Model &square, Shader &shader) {
    CellType type;
    GLfloat x, y;
    int i, j;
    for(i = 0; i < 10; ++i) {
        for(j = 0; j < 10; ++j) {
            type = board.getCell(j, i);
            x = 2.0*j/10.0-1.0;
            y = 2.0*i/10.0-1.0;
            if(type == SNAKE) {
                shader.setUniformVector("position", GL_FLOAT, 2, x, y);
                shader.setUniformVector("color", GL_FLOAT, 3, 1.0f, 1.0f, 1.0f);
                square.render(shader);
            } else if(type == FOOD) {
                shader.setUniformVector("position", GL_FLOAT, 2, x, y);
                shader.setUniformVector("color", GL_FLOAT, 3, 1.0f, 0.0f, 0.0f);
                square.render(shader);
            }
        }
    }
}

int main() {
    try {
        Snake snake = Snake(10, 10);
        Shader shader;
        Model square;
        GLfloat interval = 0.1f;
        GLfloat last_time;
        GLfloat current_time;
        Move last_move = LEFT;
        Move move;
        
        WindowManager::create("Snake", 1024, 1024);
        shader.create(RESOURCE_PATH+"shaders/default.vs", RESOURCE_PATH+"shaders/default.fs");
        loadSquare(0.0f, 0.0f, 1.9f/10, "", square);
        Shader::setWindowRatio(WindowManager::getRatio());
        
        last_time = glfwGetTime();
        while(!WindowManager::endFlag()) {
            WindowManager::initNewFotogram();
            
            current_time = glfwGetTime();
            if(current_time-last_time >= interval) {
                if(snake.end()) {
                    snake.reset();
                    last_move = LEFT;
                } else {
                    if(WindowManager::keyPressed(GLFW_KEY_A) && last_move != RIGHT)
                        move = LEFT;
                    else if(WindowManager::keyPressed(GLFW_KEY_D) && last_move != LEFT)
                        move = RIGHT;
                    else if(WindowManager::keyPressed(GLFW_KEY_W) && last_move != DOWN)
                        move = UP;
                    else if(WindowManager::keyPressed(GLFW_KEY_S) && last_move != UP)
                        move = DOWN;
                    else
                        move = last_move;
                    last_move = move;
                    snake.update(move);
                }
                last_time = glfwGetTime();
            }
            drawBoard(snake, square, shader);
            
            WindowManager::endFotogram();
        }
        
        WindowManager::destroy();
    } catch(const std::runtime_error &e) {
        std::cerr << "Fatal error: " << std::endl;
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
