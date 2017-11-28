#ifndef SRC_GAMES_CONNECTFOUR_H_
#define SRC_GAMES_CONNECTFOUR_H_

#include "gamestate.h"

#include <iostream>
#include <vector>

#define BOARD_SIZE 7
#define NUM_AXIS 4

enum Player {player_one, player_two, none};

typedef struct Square {
    Player current = none;
    // number matching in each direction starting from horizontal and moving
    // counterclockwise and upward
    short matching[NUM_AXIS] = {0,0,0,0};
} Square;

class ConnectFourState : public GameState {
public:
    ConnectFourState();
    virtual ~ConnectFourState();
    bool game_over() override;
    float get_score_heuristic() override;
    std::vector<GameState *> next_states() override;

    void output_state() override;
    void prompt_move() override;
    Player get_turn();

private:
    void update_matching(int col, int row, int col_dir, int row_dir, int matching_index, Player p);
    bool apply_move(int col_index);
    Square board[BOARD_SIZE][BOARD_SIZE];
    Player turn = player_one;
};

#endif //SRC_GAMES_CONNECTFOUR_H_
