#ifndef SRC_MINIMAX_H_
#define SRC_MINIMAX_H_

#include "../games/gamestate.h"

template <class Game>
class Minimax {
 public:
    Minimax(int max_depth, Game* gs);
    Game *minimax(Game *gs, bool is_max);

 private:

    float sim_move(Game *gs, int depth, bool is_max);
    Game *get_space(int depth, int state_size, int thread_num);
    int max_depth;
    void *state_space;
};

#include "naiveminimax.cpp"

#endif //SRC_MINIMAX_H_