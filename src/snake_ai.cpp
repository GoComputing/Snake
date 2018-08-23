#include <snake_ai.hpp>
#include <tools.hpp>
#include <queue>

struct State {
    Snake board;
    Move move;
    State *previus;
    
    State(const Snake &board, Move move, State *previus) {
        this->board = board;
        this->move = move;
        this->previus = previus;
    }
};

Move OppositeMove(Move move) {
    if(move == LEFT)
        move = RIGHT;
    else if(move == RIGHT)
        move = LEFT;
    else if(move == UP)
        move = DOWN;
    else if(move == DOWN)
        move = UP;
    return move;
}

void SnakeAI::generatePlan(const Snake &board) {
    std::vector<std::vector<bool>> visited
        = std::vector<std::vector<bool>> (board.getSizeY(), std::vector<bool> (board.getSizeX(), false));
    Move movements[] = {LEFT, RIGHT, UP, DOWN};
    int num_movements = sizeof(movements) / sizeof(Move);
    std::queue<State*> search;
    std::queue<State*> created;
    State *state;
    State *next_state;
    State *state_objective = nullptr;
    int x, y;
    int i;
    int snake_size;
    int new_snake_size;
    search.push(new State(board, NONE, nullptr));
    created.push(search.front());
    while(search.size() > 0 && state_objective == nullptr) {
        state = search.front();
        search.pop();
        x = state->board.getSnakePosX();
        y = state->board.getSnakePosY();
        if(!visited[y][x]) {
            visited[y][x] = true;
            for(i = 0; i < num_movements && state_objective == nullptr; ++i) {
                next_state = new State(state->board, movements[i], state);
                snake_size = next_state->board.getSnakeSize();
                next_state->board.update(movements[i]);
                new_snake_size = next_state->board.getSnakeSize();
                if(next_state->board.end()) {
                    delete next_state;
                } else  {
                    if(snake_size != new_snake_size)
                        state_objective = next_state;
                    else
                        search.push(next_state);
                    created.push(next_state);
                }
            }
        }
    }
    if(state_objective != nullptr) {
        while(state_objective->move != NONE) {
            plan.push_front(state_objective->move);
            state_objective = state_objective->previus;
        }
    }
    while(created.size() > 0) {
        delete created.front();
        created.pop();
    }
}

void SnakeAI::reset() {
    plan.clear();
}

Move SnakeAI::nextMove(const Snake &board) {
    Move next_move;
    if(plan.size() == 0) {
        generatePlan(board);
    }
    if(plan.size() > 0) {
        next_move = plan.front();
        plan.pop_front();
    } else {
        next_move = NONE;
    }
    return next_move;
}
