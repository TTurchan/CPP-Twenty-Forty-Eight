
#include <cstdlib>
#include <iostream>
#include <vector>
#ifndef BOARD_H
#define BOARD_H

class board {

public:
    std::vector<std::vector<int>> game_board;
    int rows;
    int cols;


    //constructor
    board(int m, int n) : rows(m), cols(n), game_board(m, std::vector<int>(n,0)) {
        int row_one = rand()%rows;
        int row_two = rand()%rows;
        int col_one = rand()%cols;
        int col_two = rand()%cols;
        while(col_two == col_one && row_one == row_two){
            row_two = rand()%rows;
            col_two = rand()%cols;
        }
        int a = (rand()%2 + 1) *2;
        int b = (rand()%2 + 1) *2;
        game_board[row_one][col_one] = a;
        game_board[row_two][col_two] = b;
    }


    ~board(){
    }


    //copyconstructor
    board(const board& other) : rows(other.rows), cols(other.cols), game_board(other.game_board){
    }



    //copy assignment
    board operator=(const board& other){
        if(this != &other){
            this-> rows = other.rows;
            this-> cols = other.cols;
            this-> game_board = other.game_board;
        }
        return *this;
    }


    std::vector<long> alpha_beta_score();



    std::vector<int> valid_moves();

    std::vector<int> valid_insertions();

    bool check_valid_move(int dir);

    int total_non_zero();

    int zero_count(std::vector<std::vector<int>>& count_board);

    int zero_count();


    void insert(int insertion_point);
    void insert(int dig, int insertion_point);


    void update_and_insert(int dir);


    void insert_random();

    int insertion_range();


    void update_no_insert(int dir);

    void update_no_insert(int dir, std::vector<std::vector<int>>& update_board);

    void update_left_no_insert();
    void update_right_no_insert();
    void update_up_no_insert();
    void update_down_no_insert();


    void update_left_no_insert(std::vector<std::vector<int>>& update_board);
    void update_right_no_insert(std::vector<std::vector<int>>& update_board);
    void update_up_no_insert(std::vector<std::vector<int>>& update_board);
    void update_down_no_insert(std::vector<std::vector<int>>& update_board);


    void print_board_state();

};


#endif
