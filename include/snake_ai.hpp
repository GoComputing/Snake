#ifndef __SNAKE_AI_HPP__
#define __SNAKE_AI_HPP__

#include <snake.hpp>
#include <list>

class SnakeAI {
private:
    std::list<Move> plan;
    
protected:
    void generatePlan(const Snake &board);
    
public:
    void reset();
    Move nextMove(const Snake &board);
};

#endif
