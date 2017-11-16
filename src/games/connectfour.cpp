#include "gamestate.h"
#include "connectfour.h"

#include <iostream>
#include <vector>


bool ConnectFourState::game_over() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            for(int axis = 0; axis < NUM_AXIS; axis++) {
                if(this->board[i][j].matching[axis] >= 4) {
                    return true;
                }
            }
        }
    }
    return false;
}

float ConnectFourState::get_score_heuristic() {
    //TODO: Implement me
    return 0;
}

std::vector<GameState> ConnectFourState::next_states() {
    //TODO: Implement me
    return std::vector<GameState>();
}

int main() {
    std::cout << "Welcome to connect four!\n";
    return 0;
}