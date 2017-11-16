#ifndef SRC_GAMES_GAMESTATE_H_
#define SRC_GAMES_GAMESTATE_H_

#include <iostream>
#include <vector>

// Abstract class that contains the game state and functions for minimax
class GameState {
public:
    virtual float get_score_heuristic() = 0;
    virtual bool game_over() = 0;
    virtual std::vector<GameState> next_states() = 0;

    // Outputs state of the game to terminal
    virtual void output_state() = 0;
    // Prompts user for next move and updates based on input
    virtual void prompt_move() = 0;
};


#endif // SRC_GAMES_GAMESTATE_H_