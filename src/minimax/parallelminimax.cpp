#include "minimax.h"
#include <time.h>
#include <string.h>
#include <vector>
#include <omp.h>

#define EPSILON std::numeric_limits<float>::epsilon()
#define DEPTH_FACTOR 0.00001

Minimax::Minimax(int max_depth, GameState *gs) : max_depth(max_depth) {
    this->state_space = (GameState *)malloc(gs->get_size() * max_depth * gs->get_branching_factor());
}

GameState *Minimax::get_space(int depth, int state_size, int thread_num) {
    // return (GameState *)((char *)this->state_space + 
    //                             (thread_num * (state_size * max_depth)) + 
    //                             state_size*depth);

    return (GameState *) malloc(state_size);
}

GameState *Minimax::minimax(GameState *gs, bool is_max) {
    clock_t t = omp_get_wtime();
    float best_state_score = is_max ? -1 : 1;
    GameState *best_state = (GameState *)malloc(gs->get_size());

    int bfactor = gs->get_branching_factor();

    #pragma omp parallel shared(best_state_score, best_state, is_max, gs) num_threads(bfactor)
    {
        bool is_valid;
        GameState *current = this->get_space(0, gs->get_size(), 0);
        gs->next_state(current, omp_get_thread_num(), &is_valid);
        if(is_valid) {
            float score = this->sim_move(current, 1, !is_max);
            std::cout << "Thread: " << omp_get_thread_num() << " score " << score << "\n";
            #pragma omp critical
            {
                if ((is_max && score > best_state_score) || (!is_max && score < best_state_score)) {
                    memmove(best_state, current, gs->get_size());
                    best_state_score = score;
                }
            }
        }
    }

    std::cout << "Score heuristic after my move is: " << best_state_score << "\n";
    std::cout << "Calculated in: " << (omp_get_wtime() - t) << " seconds\n";
    return best_state;
}

float Minimax::sim_move(GameState *gs, int depth, bool is_max) {
    bool done = gs->game_over();
    if (done || depth >= this->max_depth) {
        float s = gs->get_score_heuristic();
        if (done) {
            // TODO: FIX THIS TO ACCOUNT FOR WHO IS IS_MAX
            s += DEPTH_FACTOR * depth * s * (-1.0);
        }
        return s;
    }
    float optimal_state_score = is_max ? -1 : 1;

    GameState *current = this->get_space(depth, gs->get_size(), omp_get_thread_num());
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