#include <motor.hpp>
#include <snake.hpp>
#include <snake_ai.hpp>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>

void drawBoard(const Snake &board, const Model &snake_model, const Model &food_model, Shader &shader) {
    CellType type;
    GLfloat x, y;
    int i, j;
    for(i = 0; i < board.getSizeY(); ++i) {
        for(j = 0; j < board.getSizeX(); ++j) {
            type = board.getCell(j, i);
            x = 2.0*j/board.getSizeX()-1.0;
            y = 2.0*i/board.getSizeY()-1.0;
            if(type == SNAKE) {
                shader.setUniformVector("position", GL_FLOAT, 2, x, y);
                shader.setUniformVector("color", GL_FLOAT, 3, 1.0f, 1.0f, 1.0f);
                snake_model.render(shader);
            } else if(type == FOOD) {
                shader.setUniformVector("position", GL_FLOAT, 2, x, y);
                shader.setUniformVector("color", GL_FLOAT, 3, 1.0f, 0.0f, 0.0f);
                food_model.render(shader);
            }
        }
    }
}

int main(int argc, char **argv) {
    const std::string HUMAN = "human";
    const std::string AI = "ai";
    
    if(argc != 2 || (argv[1] != HUMAN && argv[1] != AI)) {
        std::cerr << "Invalid program argumentos. Accepted arguments are: " << std::endl;
        std::cerr << "  " << HUMAN << " - Plays human" << std::endl;
        std::cerr << "  " << AI << "    - Plays ai" << std::endl;
        return -1;
    }
    
    srand(time(NULL));
    
    try {
        Snake snake = Snake(100, 100);
        Shader shader;
        Model snake_model;
        Model food_model;
        GLfloat interval = 0.001f;
        GLfloat last_time;
        GLfloat current_time;
        Move last_move = LEFT;
        Move move;
        SnakeAI snake_ai;
        
        WindowManager::create("Snake", 1024, 1024);
        shader.create(RESOURCE_PATH+"shaders/default.vs", RESOURCE_PATH+"shaders/default.fs");
        loadSquare(0.0f, 0.0f, 1.9f/snake.getSizeY(), RESOURCE_PATH+"textures/default.bmp", food_model);
        loadSquare(0.0f, 0.0f, 1.9f/snake.getSizeY(), "", snake_model);
        Shader::setWindowRatio(WindowManager::getRatio());
        
        last_time = glfwGetTime();
        while(!WindowManager::endFlag()) {
            WindowManager::initNewFotogram();
            
            current_time = glfwGetTime();
            if(current_time-last_time >= interval) {
                if(snake.end()) {
                    snake.reset();
                    last_move = LEFT;
                    snake_ai.reset();
                } else {
                    if(argv[1] == HUMAN) {
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
                        
                    } else {
                        move = snake_ai.nextMove(snake);
                    }
                    if(move == NONE) {
                        std::cout << "Nooooooo" << std::endl;
                        snake.reset();
                        last_move = LEFT;
                        snake_ai.reset();
                    } else {
                        last_move = move;
                        snake.update(move);
                    }
                }
                last_time = glfwGetTime();
            }
            drawBoard(snake, snake_model, food_model, shader);
            
            WindowManager::endFotogram();
        }
        
        WindowManager::destroy();
    } catch(const std::runtime_error &e) {
        std::cerr << "Fatal error: " << std::endl;
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
