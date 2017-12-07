#include "connectfour.h"
#include "../minimax/minimax.h"

#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>

#define DEPTH 8


ConnectFourState::ConnectFourState() {}

bool ConnectFourState::game_over() {
    return this->winner != none;
}

int ConnectFourState::get_branching_factor() {
    return BOARD_SIZE;
}

int ConnectFourState::get_size() {
    return sizeof(ConnectFourState);
}

float ConnectFourState::get_score_heuristic() {
    if (this->winner != none) {
        return this->winner == player_one ? -1 : 1;
    }
    // Divide by an overestimate of the theoretical maximum score
    return (-1.0) * this->heuristic / (3.0 * BOARD_SIZE * BOARD_SIZE);
}

bool ConnectFourState::next_state(ConnectFourState *gs, int n, bool *is_valid) {
    if (n >= BOARD_SIZE) {
        *is_valid = false;
        return false;
    }
    *is_valid = true;
    ConnectFourState *s = new (gs) ConnectFourState(*this);
    if (s->apply_move(n)) {
        return true;
    } else {
        *is_valid = false;
        return true;
    }
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

    int multiplier = this->turn == player_one ? 1 : -1;

    count -= 1; // Don't double count the central square
    int len = count;
    while(count > 0) {
        curr_c += col_dir;
        curr_r += row_dir;
        this->heuristic -= multiplier*this->board[curr_c][curr_r].matching[matching_index];
        this->heuristic += multiplier*len;
        this->board[curr_c][curr_r].matching[matching_index] = len;
        if (len >= 4) {
            this->winner = this->turn;
        }
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

    if (this->turn == player_one) {
        this->turn = player_two;
    } else {
        this->turn = player_one;
    }

    return true;
}

void ConnectFourState::prompt_move() {
    bool filled = false;
    int col_index;
    while(!filled) {
        std::cout << "Column to place piece: ";
        std::cin >> col_index;
        filled = this->apply_move(col_index);
    }
}

Player ConnectFourState::get_turn() {
    return this->turn;
}

int main(int argc, char** argv) {
    std::cout << "Welcome to connect four!\n";

    bool play_self = false;
    if (argc > 1 && strcmp(argv[1], "--self") == 0) {
        play_self = true;
    }

    // why did you make this a pointer? there's no need to do so 
    // I think this would actually cause a memory leak
    ConnectFourState *game = new ConnectFourState();
    Minimax<ConnectFourState> minimax(DEPTH, game);

    bool is_user_turn = true;
    while (!game->game_over()) {
        if (is_user_turn) {
            game->output_state();
            if (play_self) {
                ConnectFourState *new_state = minimax.minimax(game, false);
                delete game;
                game = new_state;
            } else {
                game->prompt_move();
            }
        } else {
            game->output_state();
            ConnectFourState *new_state = minimax.minimax(game, true);
            delete game;
            game = new_state;

        }
        is_user_turn = !is_user_turn;
    }

    game->output_state();
    std::cout << "Winner is: " << (game->get_score_heuristic() == 1 ? "BLUE" : "RED") << std::endl;

    return 0;
}
