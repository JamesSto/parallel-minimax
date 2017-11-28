#ifndef SRC_MINIMAX_H_
#define SRC_MINIMAX_H_

#include "games/gamestate.h"

class Minimax {
 public:
    explicit Minimax(int max_depth);
    GameState *minimax(GameState *gs);

 private:
    float sim_maximizer(GameState *gs, int depth);
    float sim_minimizer(GameState *gs, int depth);
    int max_depth;
};

#endif //SRC_MINIMAX_H_