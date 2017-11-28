#ifndef SRC_MINIMAX_H_
#define SRC_MINIMAX_H_

#include "games/gamestate.h"

class Minimax {
 public:
    explicit Minimax(int max_depth);
    GameState *minimax(GameState *gs);

 private:
    float sim_move(GameState *gs, int depth, bool is_max);
    int max_depth;
};

#endif //SRC_MINIMAX_H_