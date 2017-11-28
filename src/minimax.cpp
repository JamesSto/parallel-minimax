#include "minimax.h"

#include <vector>

Minimax::Minimax(int max_depth) : max_depth(max_depth) {}

GameState *Minimax::minimax(GameState *gs) {
    auto new_states = gs->next_states();
    float max_state_score = -1;
    int max_state = -1;
    for (int i = 0; i < new_states.size(); i++) {
        float score = this->sim_move(new_states[i], 1, false);
        if (score > max_state_score) {
            max_state = i;
            max_state_score = score;
        }
    }
    return new_states[max_state];
}

float Minimax::sim_move(GameState *gs, int depth, bool is_max) {
    if (gs->game_over() || depth >= this->max_depth) {
        std::cout << "max term " << gs->get_score_heuristic() << " " << depth << std::endl;
        return gs->get_score_heuristic();
    }
    auto new_states = gs->next_states();
    float superlative_state_score;
    if (is_max) {
        superlative_state_score = -1;
    } else {
        superlative_state_score = 1;
    }
    for (int i = 0; i < new_states.size(); i++) {
        float score = this->sim_move(new_states[i], depth + 1, !is_max);
        if ((score > superlative_state_score && is_max) || (score < superlative_state_score && !is_max)) {
            superlative_state_score = score;
        } 
    }
    return superlative_state_score;
}