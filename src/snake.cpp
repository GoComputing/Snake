#include <cassert>
#include <snake.hpp>
#include <tools.hpp>

void Snake::initCells(int size_x, int size_y) {
    PosSnake posSnake;
    int xPosSnake;
    int yPosSnake;
    size_t i, j;
    // Empty board
    cells = std::vector<std::vector<CellType>> (size_y, std::vector<CellType> (size_x));
    for(i = 0; i < cells.size(); ++i)
        for(j = 0; j < cells[0].size(); ++j)
            cells[i][j] = EMPTY;
    // Positioning snake
    xPosSnake = cells.size() / 2;
    yPosSnake = cells[0].size() / 2;
    snake.clear();
    for(i = 0; i < INIT_SNAKE_SIZE; ++i) {
        posSnake.x = xPosSnake+i;
        posSnake.y = yPosSnake;
        cells[posSnake.y][posSnake.x] = SNAKE;
        snake.push_back(posSnake);
    }
    // Positioning objective
    putFood();
    endFlag = false;
}

void Snake::putFood() {
    int xPosScore;
    int yPosScore;
    do {
        xPosScore = UniformInt(0, cells.size());
        yPosScore = UniformInt(0, cells[0].size());
    } while(cells[yPosScore][xPosScore] != EMPTY);
    cells[yPosScore][xPosScore] = FOOD;
}

Snake::Snake(int size_x, int size_y) {
    initCells(size_x, size_y);
}

CellType Snake::getCell(int x, int y) const {
    assert((int)cells.size() > 0 && y < (int)cells.size() && x < (int)cells[0].size());
    return cells[y][x];
}

void Snake::update(Move move) {
    if(!endFlag) {
        PosSnake pos;
        PosSnake last_pos;
        pos.x = snake.front().x;
        pos.y = snake.front().y;
        switch(move) {
        case UP:    pos.y += 1; break;
        case DOWN:  pos.y -= 1; break;
        case LEFT:  pos.x -= 1; break;
        case RIGHT: pos.x += 1; break;
        }
        // TO-DO
        endFlag = !inRange(pos.y, 0, (int)cells.size()-1) || !inRange(pos.x, 0, (int)cells[0].size()-1);
        if(!endFlag) {
            if(cells[pos.y][pos.x] == EMPTY) {
                last_pos = snake.back();
                snake.pop_back();
                snake.push_front(pos);
                cells[last_pos.y][last_pos.x] = EMPTY;
                cells[pos.y][pos.x] = SNAKE;
            } else if(cells[pos.y][pos.x] == FOOD) {
                snake.push_front(pos);
                cells[pos.y][pos.x] = SNAKE;
                putFood();
            } else { // It is snake, dead
                endFlag = true;
            }
        }
    }
}

bool Snake::end() const {
    return endFlag;
}

void Snake::reset() {
    initCells(cells[0].size(), cells.size());
}

void Snake::reset(int new_size_x, int new_size_y) {
    initCells(new_size_x, new_size_y);
}