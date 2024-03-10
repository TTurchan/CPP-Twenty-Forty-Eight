#include "board.h"

long find_score(std::vector<long> score_vector, int x1, int x2, int x3);



std::vector<long> minimax(board currentBoard, int depth, bool isMaximizingPlayer, int x1, int x2, int x3, long alpha, long beta);


std::vector<board> test_dir(board& curr_board, int dir, int x1, int x2, int x3);



int minimax_run(int r, int c, int d, int x1, int x2, int x3);

