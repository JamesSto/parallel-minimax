#ifndef SRC_MINIMAX_H_
#define SRC_MINIMAX_H_

#include "games/gamestate.h"

class Minimax {
 public:
    Minimax();
    GameState *minimax(GameState *gs);

 private:
    float sim_maximizer(GameState *gs);
    float sim_minimizer(GameState *gs);
};

#endif //SRC_MINIMAX_H_