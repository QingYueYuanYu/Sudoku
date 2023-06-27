#include <random>
#include <fstream>
#include <iostream>
#include <time.h>
#include "Game.h"
using namespace std;

Game::Game(){
    board_num = 10;
    path = "game.txt";
    difficulty = 0;
    min_hole_num = 20;
    max_hole_num = 55;
    is_unique = false;
}

Game::Game(int board_n, string pat, int diff, int min_hole_n, int max_hole_n, bool is_uni){
    board_num = board_n;
    path = pat;
    difficulty = diff;
    min_hole_num = min_hole_n;
    max_hole_num = max_hole_n;
    is_unique = is_uni;
}

void Game::generate_game(){
    for(int i=0; i<board_num; i++){
        Board board;
        srand((unsigned)time(NULL)*i);
        int hole_num = min_hole_num + rand()%(max_hole_num-min_hole_num);
        board.set_hole_num(hole_num);
        board.set_difficulty(difficulty);
        board.set_unique(is_unique);
        board.generate();
        boards.push_back(board);
    }
}

void Game::out_to_file(){
    fstream f;
    f.open(path, ios::out);
    f.close();
    for(int i=0; i<board_num; i++){
        boards[i].out_to_file(path);
        f.open(path, ios::in);
        f<<"--------------------------------------";
        f.close();
    }
}