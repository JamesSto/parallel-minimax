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

#ifdef NAIVE
#include "naiveminimax.cpp"
#endif

#ifdef PARALLEL
#include "parallelminimax.cpp"
#endif

#ifdef TASK
#include "taskminimax.cpp"
#endif

#ifdef TUNED
#include "tunedminimax.cpp"
#endif


#endif //SRC_MINIMAX_H_