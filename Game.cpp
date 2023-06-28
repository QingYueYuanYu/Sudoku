#include <random>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <time.h>
#include "Game.h"
using namespace std;

Game::Game(){
    board_num = 10;
    solve_out_path = "sudoku.txt";
    generate_out_path = "game.txt";
    difficulty = 0;
    min_hole_num = 20;
    max_hole_num = 55;
    is_unique = false;
}

Game::Game(int board_n, string in_pat, string out_pat, int diff, int min_hole_n, int max_hole_n, bool is_uni){
    board_num = board_n;
    in_path = in_pat;
    solve_out_path = "sudoku.txt";
    generate_out_path = out_pat;
    difficulty = diff;
    min_hole_num = min_hole_n;
    max_hole_num = max_hole_n;
    is_unique = is_uni;
}

void Game::generate_game(){
    srand((unsigned)time(NULL));
    for(int i=0; i<board_num; i++){
        Board board;
        int hole_num = min_hole_num + rand()%(max_hole_num-min_hole_num);
        // cout<<"generate_game(): hole_num: "<<hole_num<<endl;
        board.set_hole_num(hole_num);
        board.set_difficulty(difficulty);
        board.set_unique(is_unique);
        board.generate();
        boards.push_back(board);
    }
    // cout<<"-----After Generate Game-----"<<endl;
}

void Game::solve_game(){
    for(int index=0; index<board_num; index++){
        // cout<<"Board "<<index<<" : "<<endl;
        // boards[index].output();
        boards[index].solve();
        // cout<<"Finish Board "<<index<<" Solve"<<endl;
    }
    // cout<<"-----Finish Game Solve-----"<<endl;
}

void Game::in_from_file(){
    vector<int> values;
    ifstream f(in_path);
    string line;
    getline(f, line);
    sscanf(line.c_str(), "Total Board: %d", &board_num);
    getline(f, line);
    for(int board_index=0; board_index<board_num; board_index++){
        for(int line_index=0; line_index<9; line_index++){
            stringstream f_line(line);
            string value;
            while(f_line>>value){
                if(value == "$"){
                    values.push_back(0);
                }else{
                    values.push_back(stoi(value));
                }
            }
            getline(f, line);
        }
        Board board;
        board.reset_values(values);
        boards.push_back(board);
        values.clear();
        getline(f, line);
    }
}

void Game::out_to_file(string out_path){
    fstream f;
    f.open(out_path, ios::out);
    f<<"Total Board: "<<board_num<<"\n";
    f.close();
    for(int i=0; i<board_num; i++){
        // cout<<"-----Output Board: "<<i<<"-----"<<endl;
        boards[i].out_to_file(out_path);
        f.open(out_path, ios::out|ios::app);
        f<<"-------------------"<<"\n";
        f.close();
    }
}

void Game::generate_out_to_file(){
    out_to_file(generate_out_path);
}

void Game::solve_out_to_file(){
    out_to_file(solve_out_path);
}