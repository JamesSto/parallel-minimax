#ifndef SRC_GAMES_CONNECTFOUR_H_
#define SRC_GAMES_CONNECTFOUR_H_

#include <iostream>
#include <vector>

#define BOARD_SIZE 7
#define NUM_AXIS 4

enum Player : char {player_one, player_two, none};

typedef struct Square {
    Player current = none; 
    // number matching in each direction starting from horizontal and moving
    // counterclockwise and upward
    char matching[NUM_AXIS] = {0,0,0,0};
} Square;

class ConnectFourState {
public:
    ConnectFourState();
    bool game_over();
    float get_score_heuristic();
    bool next_state(ConnectFourState *gs, int n, bool *is_valid);

    void output_state();
    void prompt_move();
    int get_size();
    int get_branching_factor();
    Player get_turn();


private:
    void update_matching(int col, int row, int col_dir, int row_dir, int matching_index, Player p);
    bool apply_move(int col_index);
    Square board[BOARD_SIZE][BOARD_SIZE];
    Player turn = player_one;
    Player winner = none;
    int heuristic = 0;
};

#endif //SRC_GAMES_CONNECTFOUR_H_
