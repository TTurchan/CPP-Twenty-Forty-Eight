#include "board.h"
#include <vector>


std::vector<long> board::alpha_beta_score(){
    int max_val=0;
    int row_collapses;
    int zeros;
    int col_collapses;
    int top_row_total;
    int weighted_snake_distance;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j<cols; j++){
            if(game_board[i][j] == 0){
                zeros++;
            } else {
                if(game_board[i][j] > max_val){
                    max_val = game_board[i][j];
                }
                //the next block will count the top row total and the collapses of rows and columns
                if(i == 0){
                    top_row_total+=game_board[i][j];
                }
                //I am not going to actually utilize this particular heuristic for the time being, because it will substantially complicate the adversarial selection algorithm.
                //I think that this is a tractable problem which won't increase computation time particularly much if carried out properly, but I want to get a functioning alpha-beta-pruning
                //solution before I work on refining the heuristics, and merely counting zeros is sufficient for the time being.
                /*
                if (i>0){
                    if(game_board[i-1][j] == game_board[i][j]){
                        col_collapses++;
                    }
                }
                if (j>0){
                    if(game_board[i][j-1] == game_board[i][j]){
                        row_collapses++;
                    }
                }
                */
                //END OF UNUSED BLOCK
                //now we will calculate the snake distance and then weight it.
                int dist = (rows-1-i)*cols;
                //the snake direction will depend on the parity of the number of rows, but this isn't important to the ultimate result or the functionality of the algorithm
                if(i%2 == 0){
                    dist+= cols-j;
                } else {
                    dist+=j;
                }
                weighted_snake_distance += dist*game_board[i][j]/100;
            }
        }
    }
    std::vector<long> result = {zeros, top_row_total, weighted_snake_distance, max_val};
    return result;
}


int board::zero_count(std::vector<std::vector<int>>& count_board){
    int zeros = 0;
    for(std::vector<int> row: count_board){
        for(int val: row){
            if(val == 0){
                zeros++;
            }
        }
    }
    return zeros;
}

int board::zero_count(){
    int zeros = 0;
    for(std::vector<int> row : game_board){
        for(int val : row){
            if(val == 0){
                zeros++;
            }
        }
    }
    return zeros;
}



int board::total_non_zero(){
    int tot =0;
    for(std::vector<int> row : game_board){
        for(int val : row){
            tot+=val;
        }
    }
    return tot;
}





bool board::check_valid_move(int dir){
    std::vector<std::vector<int>> copy = game_board;
    update_no_insert(dir, copy);
    if (copy != game_board){
        return true;
    }
    return false;

}

void board::update_no_insert(int dir){
    //0-> up, 1-> down, 2-> left, 3->right
    if (dir == 0){
        update_up_no_insert();
    } else if(dir == 1){
        update_down_no_insert();
    } else if(dir == 2){
        update_left_no_insert();
    } else if(dir == 3){
        update_right_no_insert();
    }
}



void board::update_no_insert(int dir, std::vector<std::vector<int>>& update_board){
    //0-> up, 1-> down, 2-> left, 3->right
    if (dir == 0){
        update_up_no_insert(update_board);
    } else if(dir == 1){
        update_down_no_insert(update_board);
    } else if(dir == 2){
        update_left_no_insert(update_board);
    } else if(dir == 3){
        update_right_no_insert(update_board);
    }
}


void board::update_left_no_insert(std::vector<std::vector<int>>& update_board){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< rows; i++){
        temp = -1;
        insertion_ind =0;
        for (int j=0; j < cols; j++){
            if (update_board[i][j] != 0){
                if (temp == -1){
                    temp = update_board[i][j];
                } else if (temp == update_board[i][j]){
                    update_board[i][insertion_ind] = temp*2;
                    temp = -1;
                    insertion_ind++;
                } else {
                    update_board[i][insertion_ind] = temp;
                    temp = update_board[i][j];
                    insertion_ind++;
                }
            }
        }
        if (temp != -1){
            update_board[i][insertion_ind] = temp;
            insertion_ind++;
        }
        while(insertion_ind < cols){
            update_board[i][insertion_ind] = 0;
            insertion_ind++;
        }
    }
}
void board::update_up_no_insert(std::vector<std::vector<int>>& update_board){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< cols; i++){
        insertion_ind =0;
        temp = -1;
        for (int j=0; j < rows; j++){
            if (update_board[j][i] != 0){
                if (temp == -1){
                    temp = update_board[j][i];
                } else if (temp == update_board[j][i]){
                    update_board[insertion_ind][i] = temp*2;
                    temp = -1;
                    insertion_ind++;
                } else {
                    update_board[insertion_ind][i] = temp;
                    temp = update_board[j][i];
                    insertion_ind++;
                }
            }

        }

        if (temp != -1){
            update_board[insertion_ind][i] = temp;
            insertion_ind++;
        }
        while(insertion_ind < rows){
            update_board[insertion_ind][i] = 0;
            insertion_ind++;
        }
    }
}
void board::update_right_no_insert(std::vector<std::vector<int>>& update_board){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< rows; i++){
        temp = -1;
        insertion_ind =cols-1;
        for (int j=cols-1; j>=0; j--){
            if (update_board[i][j] != 0){
                if (temp == -1){
                    temp = update_board[i][j];
                } else if (temp == update_board[i][j]){
                    update_board[i][insertion_ind] = temp*2;
                    temp = -1;
                    insertion_ind--;
                } else {
                    update_board[i][insertion_ind] = temp;
                    temp = update_board[i][j];
                    insertion_ind--;
                }
            }
        }
        if (temp != -1){
            update_board[i][insertion_ind] = temp;
            insertion_ind--;
        }
        while(insertion_ind >=0){
            update_board[i][insertion_ind] = 0;
            insertion_ind--;
        }
    }
}
void board::update_down_no_insert(std::vector<std::vector<int>>& update_board){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< cols; i++){
        temp = -1;
        insertion_ind =rows-1;
        for (int j=rows-1; j>=0; j--){
            if (update_board[j][i] != 0){
                if (temp == -1){
                    temp = update_board[j][i];
                } else if (temp == update_board[j][i]){
                    update_board[insertion_ind][i] = temp*2;
                    temp = -1;
                    insertion_ind--;
                } else {
                    update_board[insertion_ind][i] = temp;
                    temp = update_board[j][i];
                    insertion_ind--;
                }
            }

        }
        if (temp != -1){
            update_board[insertion_ind][i] = temp;
            insertion_ind--;
        }
        while(insertion_ind >=0){
            update_board[insertion_ind][i] = 0;
            insertion_ind--;
        }
    }
}


void board::update_left_no_insert(){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< rows; i++){
        temp = -1;
        insertion_ind =0;
        for (int j=0; j < cols; j++){
            if (game_board[i][j] != 0){
                if (temp == -1){
                    temp = game_board[i][j];
                } else if (temp == game_board[i][j]){
                    game_board[i][insertion_ind] = temp*2;
                    temp = -1;
                    insertion_ind++;
                } else {
                    game_board[i][insertion_ind] = temp;
                    temp = game_board[i][j];
                    insertion_ind++;
                }
            }
        }
        if (temp != -1){
            game_board[i][insertion_ind] = temp;
            insertion_ind++;
        }
        while(insertion_ind < cols){
            game_board[i][insertion_ind] = 0;
            insertion_ind++;
        }
    }
}
void board::update_up_no_insert(){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< cols; i++){
        insertion_ind =0;
        temp = -1;
        for (int j=0; j < rows; j++){
            if (game_board[j][i] != 0){
                if (temp == -1){
                    temp = game_board[j][i];
                } else if (temp == game_board[j][i]){
                    game_board[insertion_ind][i] = temp*2;
                    temp = -1;
                    insertion_ind++;
                } else {
                    game_board[insertion_ind][i] = temp;
                    temp = game_board[j][i];
                    insertion_ind++;
                }
            }

        }

        if (temp != -1){
            game_board[insertion_ind][i] = temp;
            insertion_ind++;
        }
        while(insertion_ind < rows){
            game_board[insertion_ind][i] = 0;
            insertion_ind++;
        }
    }
}
void board::update_right_no_insert(){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< rows; i++){
        temp = -1;
        insertion_ind =cols-1;
        for (int j=cols-1; j>=0; j--){
            if (game_board[i][j] != 0){
                if (temp == -1){
                    temp = game_board[i][j];
                } else if (temp == game_board[i][j]){
                    game_board[i][insertion_ind] = temp*2;
                    temp = -1;
                    insertion_ind--;
                } else {
                    game_board[i][insertion_ind] = temp;
                    temp = game_board[i][j];
                    insertion_ind--;
                }
            }
        }
        if (temp != -1){
            game_board[i][insertion_ind] = temp;
            insertion_ind--;
        }
        while(insertion_ind >=0){
            game_board[i][insertion_ind] = 0;
            insertion_ind--;
        }
    }
}
void board::update_down_no_insert(){
    int insertion_ind;
    int temp = -1;
    for (int i =0; i< cols; i++){
        temp = -1;
        insertion_ind =rows-1;
        for (int j=rows-1; j>=0; j--){
            if (game_board[j][i] != 0){
                if (temp == -1){
                    temp = game_board[j][i];
                } else if (temp == game_board[j][i]){
                    game_board[insertion_ind][i] = temp*2;
                    temp = -1;
                    insertion_ind--;
                } else {
                    game_board[insertion_ind][i] = temp;
                    temp = game_board[j][i];
                    insertion_ind--;
                }
            }

        }
        if (temp != -1){
            game_board[insertion_ind][i] = temp;
            insertion_ind--;
        }
        while(insertion_ind >=0){
            game_board[insertion_ind][i] = 0;
            insertion_ind--;
        }
    }
}


void board::insert(int insertion_point){
    int zeros = 0;
    int dig = 2;
    if(insertion_point < 0){
        insertion_point = -insertion_point;
        dig = 4;
    }
    for(int i=0; i < rows; i++){
        for(int j= 0; j< cols; j++){
            if(game_board[i][j] == 0){
                zeros++;
                if (zeros == insertion_point){
                    game_board[i][j] = dig;
                }

            }

        }
    }
}


void board::insert(int dig, int insertion_point){
    int zeros = 0;
    for(int i=0; i < rows; i++){
        for(int j= 0; j< cols; j++){
            if(game_board[i][j] == 0){
                zeros++;
                if (zeros == insertion_point){
                    game_board[i][j] = dig;
                }

            }

        }
    }
}


std::vector<int> board::valid_moves(){
    std::vector<int> moves = {};
    for (int i = 0; i < 4; i++){
        if(check_valid_move(i)){
            moves.push_back(i);
        }
    }
    return moves;
}


int board::insertion_range(){
    return zero_count(game_board)+1;
}


std::vector<int> board::valid_insertions(){
    std::vector<int> insertions;
    int output_range = insertion_range();
    for (int i = 1; i <= output_range; i++){
        insertions.push_back(i);
        insertions.push_back(-i);
    }
    return insertions;
}


void board::update_and_insert(int dir){
    if (check_valid_move(dir) == true){

        update_no_insert(dir, game_board);
        insert_random();
    } else {
        std::cout<<"move_invalid"<<std::endl;
    }

}


void board::print_board_state(){
    for (int i =0; i<rows; i++){
        for (int j=0; j<cols; j++){
            std::cout<< game_board[i][j] <<", ";
        }
        std::cout<< "\n";
    }
    std::cout<<"\n\n";
}



void board::insert_random(){
    int insertion_pt = rand() % zero_count(game_board)+1;
    int dig = rand() % 2;
    if (dig == 1){
        dig = 4;
    } else{
        dig = 2;
    }
    insert(dig,insertion_pt);
}


