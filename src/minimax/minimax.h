#ifndef SRC_MINIMAX_H_
#define SRC_MINIMAX_H_

#include "../games/gamestate.h"

class Minimax {
 public:
    explicit Minimax(int max_depth, GameState* gs);
    GameState *minimax(GameState *gs);

 private:
    float sim_move(GameState *gs, int depth, bool is_max);
    GameState *get_space(int depth, int state_size);
    int max_depth;
    void *state_space;
};

#endif //SRC_MINIMAX_H_