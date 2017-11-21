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
    //P1 is the maximizing player
    float score = 0;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
                float multiplier;
            if (this->board[i][j].current == player_two) {
                multiplier = -1;
            }
            else if (this->board[i][j].current == player_one){
                multiplier = 1;
            }
            else {
                multiplier = 0;
            }
            for(int n = 0; n < 4; n++) {
                // If the game is over, return -1 or 1 depending on who won
                if (this->board[i][j].matching[n] >= 4) {
                    return multiplier;
                }

                // Add to the score the number in a row at this square
                // This will triple count three in a rows, double count 2 in a rows, etc
                // Which is what we want.
                score += multiplier * this->board[i][j].matching[n];
            }
        }
    }

    // Divide by an overestimate of the theoretical maximum score
    return score / (3.0 * BOARD_SIZE * BOARD_SIZE);
}

std::vector<GameState *> ConnectFourState::next_states() {
    std::vector<GameState *> *next_states = new std::vector<GameState *>();
    for(int i = 0; i < BOARD_SIZE; i++) {
        ConnectFourState *s = new ConnectFourState(*this);
        if(s->apply_move(i)) {
            next_states->push_back(s);
        }
    }
    return *next_states;
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
    // You know how they say to never write code that you are barely smart enough to write,
    // because you'll never understand it when you go to debug it later?
    // Yeah... Let's hope this function never breaks.
    int count = 0;
    int n = 0;
    int curr_c;
    int curr_r;

    for(int dir = 1; dir > -2; dir -= 2) {
        n = 0;
        curr_c = col;
        curr_r = row;
        while (curr_c >= 0 && curr_c < BOARD_SIZE && curr_r >= 0 && curr_r < BOARD_SIZE 
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

bool ConnectFourState::apply_move(int col_index) {
    bool filled = false;
    int row_index;
    for(row_index = BOARD_SIZE-1; row_index >= 0; row_index--) {
        if (this->board[row_index][col_index].current == none) {
            this->board[row_index][col_index].current = this->turn;
            filled = true;
            break;
        }
    }
    if (!filled) {
        return false;
    }
    this->update_matching(row_index, col_index, 0, 1, 0, this->turn); //Horizontal
    this->update_matching(row_index, col_index, -1, 1, 1, this->turn); // Upper right
    this->update_matching(row_index, col_index, 1, 0, 2, this->turn); // Vertical
    this->update_matching(row_index, col_index, -1, -1, 3, this->turn); // Upper left

    return true;
}

void ConnectFourState::prompt_move() {
    bool filled = false;
    int col_index;
    int row_index;
    while(!filled) {
        std::cout << "Column to place piece: ";
        std::cin >> col_index;
        filled = this->apply_move(col_index);
    }

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
        std::cout << "**********************************\n";
        for(GameState *g : game->next_states()) {
            g->output_state();
        }
        std::cout << "**********************************\n";
        game->output_state();
        game->prompt_move();
    }

    return 0;
}
