#include "minimax.h"
#include <time.h>
#include <string.h>



#include <vector>

#define EPSILON std::numeric_limits<float>::epsilon()
#define DEPTH_FACTOR 0.00001

Minimax::Minimax(int max_depth, GameState *gs) : max_depth(max_depth) {
    this->state_space = (GameState *)malloc(gs->get_size() * max_depth);
}

GameState *Minimax::minimax(GameState *gs) {
    clock_t t = clock();
    GameState *current = (GameState *)malloc(gs->get_size());
    float max_state_score = -1;
    GameState *max_state = (GameState *)malloc(gs->get_size());

    int n = 0;
    bool is_valid;
    bool not_done = true;

    while(not_done) {
        not_done = gs->next_state(current, n, &is_valid);
        std::cout << "Getting state " << n << "\n";
        if(is_valid) {
            float score = this->sim_move(current, 1, false);
            std::cout << "Score: " << score << "\n";
            if (score > max_state_score) {
                memmove(max_state, current, gs->get_size());
                max_state_score = score;
            }
        }
        n += 1;
    }

    return max_state;
}

float Minimax::sim_move(GameState *gs, int depth, bool is_max) {
    bool done = gs->game_over();
    if (done || depth >= this->max_depth) {
        float s = gs->get_score_heuristic();
        if (done) {
            s += DEPTH_FACTOR * depth * s * (-1.0);
        }
        return s;
    }
    float optimal_state_score = is_max ? -1 : 1;

    GameState *current = (GameState *)malloc(gs->get_size());
    int n = 0;
    bool is_valid;
    bool not_done = true;

    while(not_done) {
        not_done = gs->next_state(current, n, &is_valid);
        if(is_valid) {
            float score = this->sim_move(current, depth + 1, !is_max);
            optimal_state_score = is_max ? std::max(score, optimal_state_score) : 
                                            std::min(score, optimal_state_score);
        }
        n += 1;
    }

    return optimal_state_score;
}