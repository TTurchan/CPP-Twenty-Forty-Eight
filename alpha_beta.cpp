#include "board.h"
#include "alpha_beta.h"


#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>
//score_vector format
//std::vector<int> result = {zeros, top_row_total, weighted_snake_distance, max_val};



long find_score(std::vector<long> score_vector, int x1, int x2, int x3){
    //there will be a need to perform empirical tests to determine the ideal weights
    long a = x1*score_vector[0];
    long b = x2*score_vector[1];
    long c = x3*score_vector[2];
    return a+b+c;
}


std::vector<long> minimax(board currentBoard, int depth, bool isMaximizingPlayer, int x1, int x2, int x3, long alpha, long beta){

    std::vector<long> best_score = {};

    if(isMaximizingPlayer){
        //set moves for the player chosing directions
        std::vector<int> moves = currentBoard.valid_moves();
        if(depth == 0 || moves.size() == 0){
            return {find_score(currentBoard.alpha_beta_score(), x1, x2, x3)};
        }
      //  std::sort(moves.begin(), moves.end(), [&](const int& move1, const int& move2) {
      //      board temp_board1 = currentBoard;
      //      temp_board1.update_no_insert(move1); // Or temp_board1.insert(move1); based on the context
      //      long score1 = find_score(temp_board1.alpha_beta_score(), x1, x2, x3);

      //      board temp_board2 = currentBoard;
      //      temp_board2.update_no_insert(move2); // Or temp_board2.insert(move2); based on the context
      //      long score2 = find_score(temp_board2.alpha_beta_score(), x1, x2, x3);

      //      return score1 > score2; // For maximizing player, higher scores first
      //  });

        for (int move : moves){
            board new_board = currentBoard;
            new_board.update_no_insert(move);



            std::vector<long> temp_score = minimax(new_board, depth-1, !isMaximizingPlayer, x1, x2, x3, alpha, beta);
            if(temp_score.size() < 2){
                temp_score.resize(2);
            }
            temp_score.insert(temp_score.begin()+1, move);

            if(best_score.size() == 0){
                best_score = temp_score;
                alpha = temp_score[0];
            } else {
                if(best_score[0]<temp_score[0]){
                    best_score = temp_score;
                }
                alpha = std::max(alpha, best_score[0]);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return best_score;
    } else {
        //set moves for the computer inserting random digits.
        std::vector<int> moves = currentBoard.valid_insertions();
        int zeros = currentBoard.zero_count();
        if(depth == 0 || zeros == 0){
            return {find_score(currentBoard.alpha_beta_score(), x1, x2, x3)};
        }

      //  std::sort(moves.begin(), moves.end(), [&](const int& move1, const int& move2) {
      //      board temp_board1 = currentBoard;
      //      temp_board1.insert(move1); // Or temp_board1.insert(move1); based on the context
      //      long score1 = find_score(temp_board1.alpha_beta_score(), x1, x2, x3);

      //      board temp_board2 = currentBoard;
      //      temp_board2.insert(move2); // Or temp_board2.insert(move2); based on the context
      //      long score2 = find_score(temp_board2.alpha_beta_score(), x1, x2, x3);

      //      return score1 < score2; // For minimizing player, lower scores first
      //  });

        for (int move : moves){
            board new_board = currentBoard;
            new_board.insert(move);
            std::vector<long> temp_score = minimax(new_board, depth-1, !isMaximizingPlayer, x1, x2, x3, alpha, beta);
            if(temp_score.size() < 2){
                temp_score.resize(2);
            }
            temp_score.insert(temp_score.begin()+1, move);


            if(best_score.size() == 0){
                best_score = temp_score;
                beta = temp_score[0];
            } else {
                if(best_score[0]>temp_score[0]){
                    best_score = temp_score;
                }
                beta = std::min(beta, best_score[0]);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return best_score;
    }

}


std::vector<board> test_dir(board& curr_board, int dir, int x1, int x2, int x3){
    std::vector<int> test_vector;
    std::vector<board> return_vector;


    for(int i = 0; i < 4; i++){
        board test_board = curr_board;
        test_board.update_no_insert(i, test_board.game_board);
        return_vector.push_back(test_board);
    }

    return return_vector;
}


int minimax_run(int r, int c, int d, int x1, int x2, int x3){
    board test_board(r,c);
    int max_val = 0;

    while(test_board.valid_moves().size() >0){
        int move;
        std::vector<long> minimax_output;
        for(int val : minimax_output){
            std::cout << val << ", ";
        }
        //std::cout << "\nasdfasdfasdf\n";
        minimax_output = minimax(test_board, d, true, x1, x2, x3, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        //for(int val : minimax_output){
        //    std::cout << val << std::endl;
        //}
        //std::cout << "\n";
        test_board.update_no_insert(minimax_output[1]);
        //std::cout << "the last move was " << minimax_output[1] << std::endl;

//        test_board.print_board_state();
        test_board.insert_random();
        //std::cout<<"\n";
    }
    for(std::vector<int> row : test_board.game_board){
        for(int val : row){
            if (val > max_val){
                max_val = val;
            }
        }
    }
    //std::cout << "qwerqwerqwerqwerqwer "<< max_val;

//    test_board.print_board_state();


    return max_val;
}



