#include "gamestate.h"
#include "connectfour.h"

#include <iostream>
#include <vector>


ConnectFourState::ConnectFourState() {
    return;
}

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


void ConnectFourState::output_state() {
    std::cout << "\n";
    for(int col = 0; col < BOARD_SIZE; col++) {
        std::cout << "|";
        for(int row = 0; row < BOARD_SIZE; row++) {
            switch (this->board[col][row].current) {
                case player_one:
                    // ANSI color code for red O
                    std::cout << "\033[1;31mO\033[0m";
                    break;
                case player_two:
                    // ANSI color code for blue O
                    std::cout << "\033[1;34mO\033[0m";
                    break;
                default:
                    std::cout << " ";
            }
            std::cout << "|";
        }
        std::cout << "\n";
        for(int i = 0; i < BOARD_SIZE; i++) {
            std::cout << "--";
        }
        std::cout << "-\n";
    }
    std::cout << " ";
    for(int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i;
        std::cout << " ";
    }
    std::cout << "\n";
}

void ConnectFourState::update_matching(int col, int row, int col_dir, int row_dir, int matching_index, Player p) {
    int count = 0;
    int n = 0;
    int curr_c;
    int curr_r;

    for(int dir = 1; dir > -2; dir -= 2) {
        n = 0;
        curr_c = col;
        curr_r = row;
        while (curr_c >= 0 && curr_c < BOARD_SIZE && curr_r >= 0 && curr_c < BOARD_SIZE 
            && this->board[curr_c][curr_r].current == p) {
            count += 1;
            n += 1;
            curr_c = col + n*col_dir*dir;
            curr_r = row + n*row_dir*dir;
        }
    }
    count -= 1; // Don't double count the central square
    int len = count;
    while(count > 0) {
        curr_c += col_dir;
        curr_r += row_dir;
        this->board[curr_c][curr_r].matching[matching_index] = len;
        count -= 1;
    }
}

void ConnectFourState::prompt_move() {
    bool filled = false;
    int col;
    int row;
    while(!filled) {
        std::cout << "Column to place piece: ";
        std::cin >> col;
        for(row = BOARD_SIZE-1; row >= 0; row--) {
            if (this->board[col][row].current = none) {
                this->board[col][row].current = this->turn;
                filled = true;
                break;
            }
        }
    }

    this->update_matching(col, row, 0, 1, 0, turn); //Horizontal
    this->update_matching(col, row, -1, 1, 1, turn); // Upper right
    this->update_matching(col, row, 1, 0, 2, turn); // Vertical
    this->update_matching(col, row, -1, -1, 3, turn); // Upper left

    if (this->turn == player_one) {
        this->turn = player_two;
    } else {
        this->turn = player_one;
    }
}

int main() {
    std::cout << "Welcome to connect four!\n";

    ConnectFourState *game = new ConnectFourState();
    while(true) {
        game->output_state();
        game->prompt_move();
    }

    return 0;
}
