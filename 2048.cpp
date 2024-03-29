#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "board.h"
#include "alpha_beta.h"


int main(){
//    std::cout<<"asdfasdfasdf";
//    board new_board(4,4);
//    int rand_dir;
//    srand(static_cast<unsigned int>(time(NULL)));
//    for (int i=0; i<1000; i++) {
//        rand_dir = rand()%4;
//        new_board.update_and_insert(rand_dir);
//        new_board.print_board_state();
//
//
//    }
//    std::cout<<"\nqwerqwerqwerweqr";
    srand(static_cast<unsigned int>(time(NULL)));
//
    int max_val = 0;
    float avg_dur;
    int runs = 0;
    int total_max;

    auto tot_start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 20; i++){
        runs++;

        //auto start = std::chrono::high_resolution_clock::now();
        int val = minimax_run(4, 4, 5, 20, 0, 10);
        //auto stop = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        //std::cout<< "execution took " << duration.count() << " ms." << std::endl;
        max_val = std::max(max_val, val);
        total_max+=val;

        std::cout<<val<<std::endl;
    }

    auto tot_stop = std::chrono::high_resolution_clock::now();

    auto tot_dur = std::chrono::duration_cast<std::chrono::milliseconds>(tot_stop-tot_start);
    int final = total_max/runs;
    std::cout<< "average total " << final <<"\n";
    std::cout<< "tot execution took " << tot_dur.count() << " ms." << std::endl;
    std::cout<<max_val;
    return 0;

    //1766 for 4,0,1
    //1834 for 3,0,1
    //3481 for 2,0,1 **** probably between 2:1 and 3:1
    //1715 for 1,0,1
    //3737 for 5,0,2
    //
    //
    //1151 2,0,1
    //1190 20,0,10
    //1036 28,0,10
    //1151 18,0,10
    //1100 12,0,10
}
