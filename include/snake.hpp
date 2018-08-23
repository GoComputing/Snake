#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <iostream>
#include <vector>
#include <list>

enum CellType {EMPTY, SNAKE, FOOD};
enum Move {UP, DOWN, LEFT, RIGHT, NONE};

class Snake {
private:
    struct PosSnake {
        int x;
        int y;
    };
    
    static constexpr int INIT_SNAKE_SIZE = 3;
    static constexpr int MIN_SIZE_X = INIT_SNAKE_SIZE*2;
    static constexpr int MAX_SIZE_X = MIN_SIZE_X;
    std::vector<std::vector<CellType>> cells;
    std::list<PosSnake> snake;
    int objective_x;
    int objective_y;
    bool endFlag;
    
protected:
    void initCells(int size_x, int size_y);
    void putFood();
    
public:
    Snake();
    Snake(int size_x, int size_y);
    
    CellType getCell(int x, int y) const;
    int getSizeX() const;
    int getSizeY() const;
    int getSnakePosX() const;
    int getSnakePosY() const;
    int getObjectivePosX() const;
    int getObjectivePosY() const;
    int getSnakeSize() const;
    void update(Move move);
    bool end() const;
    
    void reset();
    void reset(int new_size_x, int new_size_y);
};

std::ostream& operator<<(std::ostream &os, Move move);

#endif
