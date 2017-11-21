#include "minimax.h"

#include <vector>

GameState *Minimax::minimax(GameState *gs) {
    auto new_states = gs->next_states();
    float max_state_score = -1;
    int max_state = -1;
    for (int i = 0; i < new_states.size(); i++) {
        float score = this->sim_maximizer(new_states[i]);
        if (score > max_state_score) {
            max_state = i;
            max_state_score = score;
        }
    }
    return new_states[max_state];
}

float Minimax::sim_maximizer(GameState *gs) {
    if (gs->game_over()) {
        return gs->get_score_heuristic();
    }
    auto new_states = gs->next_states();
    float max_state_score = -1;
    for (int i = 0; i < new_states.size(); i++) {
        float score = this->sim_minimizer(new_states[i]);
        if (score > max_state_score) {
            max_state_score = score;
        }
    }
    return max_state_score;
}

float Minimax::sim_minimizer(GameState *gs) {
    if (gs->game_over()) {
        return gs->get_score_heuristic();
    }
    auto new_states = gs->next_states();
    float min_state_score = 1;
    for (int i = 0; i < new_states.size(); i++) {
        float score = this->sim_maximizer(new_states[i]);
        if (score < min_state_score) {
            min_state_score = score;
        }
    }
    return min_state_score;
}
