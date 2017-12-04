#include "minimax.h"
#include <time.h>


#include <vector>

#define EPSILON std::numeric_limits<float>::epsilon()
#define DEPTH_FACTOR 0.00001

Minimax::Minimax(int max_depth) : max_depth(max_depth) {}

GameState *Minimax::minimax(GameState *gs) {
    clock_t t = clock();
    auto new_states = gs->next_states();
    float max_state_score = -1;
    GameState *max_state = new_states[0];
    for (GameState *gs : new_states) {
        float score = this->sim_move(gs, 1, false);
        if (score > max_state_score) {
            max_state = gs;
            max_state_score = score;
        }
    }
    std::cout << "Score heuristic after my move is: " << max_state_score << "\n";
    std::cout << "Calculated in: " << ((float)(clock() - t)/CLOCKS_PER_SEC) << " seconds\n";
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
    auto new_states = gs->next_states();

    float optimal_state_score = is_max ? -1 : 1;

    for (GameState *gs : new_states) {
        float score = this->sim_move(gs, depth + 1, !is_max);
        optimal_state_score = is_max ? std::max(score, optimal_state_score) : 
                                       std::min(score, optimal_state_score);
    }
    return optimal_state_score;
}