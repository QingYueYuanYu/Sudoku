#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Game.h"

using namespace std;
void extract_param(int argc, char* argv[], int &board_num, bool &is_generate, string &input_path, int &game_num, int &difficulty, int &min_hole_num, int &max_hole_num, bool &is_unique){
    for(int arg_index=0; arg_index<argc; arg_index++){
        if(strcmp(argv[arg_index],"-c") == 0){
            board_num = atoi(argv[arg_index+1]);
        }else if(strcmp(argv[arg_index],"-s") == 0){
            is_generate = false;
            input_path = argv[arg_index+1];
        }else if(strcmp(argv[arg_index],"-n") == 0){
            game_num = atoi(argv[arg_index+1]);
        }else if(strcmp(argv[arg_index],"-m") == 0){
            difficulty = atoi(argv[arg_index+1]);
        }else if(strcmp(argv[arg_index],"-r") == 0){
            string tmp(argv[arg_index+1]), min_hole_num_str, max_hole_num_str;
            istringstream str_stream(tmp);
            getline(str_stream, min_hole_num_str, '~');
            getline(str_stream, max_hole_num_str, '~');
            // cout<<"min_hole_num_str: "<<min_hole_num_str<<" max_hole_num_str: "<<max_hole_num_str<<endl;
            min_hole_num = stoi(min_hole_num_str);
            max_hole_num = stoi(max_hole_num_str);
        }else if(strcmp(argv[arg_index],"-u") == 0){
            is_unique = true;
        }
    }
}

bool check_param(int &board_num, bool &is_generate, string &input_path, int &game_num, int &difficulty, int &min_hole_num, int &max_hole_num, bool &is_unique){
    if(game_num==0 && (difficulty!=0 || min_hole_num!=0 || max_hole_num!=0 || is_unique)){
        cout<<"Error Param: You have to specified n. "<<endl;
        return false;
    }else if(board_num<1 || board_num>1000000){
        cout<<"Board num out of bound, you have to set it between [1, 1000000]"<<endl;
        return false;
    }else if(game_num!=0 && (game_num<1 || game_num>10000)){
        cout<<"Game num out of bound, you have to set it between [1, 10000]"<<endl;
        return false;
    }else if(difficulty!=0 && (difficulty<1 || difficulty>3)){
        cout<<"Difficulty out of bound, you have to set it between [1, 3]"<<endl;
        return false;
    }else if((min_hole_num!=0 && min_hole_num<20) || (max_hole_num!=0 && max_hole_num>55)){
        cout<<"Hole num out of bound, you have to set it between [20, 55]"<<endl;
        return false;
    }
    return true;
}

void set_uninitialized_param(int &board_num, bool &is_generate, string &input_path, int &game_num, int &difficulty, int &min_hole_num, int &max_hole_num, bool &is_unique){
    if(game_num == 0){
        game_num = 1;
    }
    if(difficulty == 0){
        difficulty = 1;
    }
    if(min_hole_num == 0){
        min_hole_num = 20;
    }
    if(max_hole_num == 0){
        max_hole_num = 55;
    }
}

void generate(int &board_num, string &in_path, int &game_num, int &difficulty, int &min_hole_num, int &max_hole_num, bool &is_unique){
    for(int game_index=0; game_index<game_num; game_index++){
        string out_path = "game" + to_string(game_index) + ".txt";
        Game game(board_num, in_path, out_path, difficulty, min_hole_num, max_hole_num, is_unique);
        game.generate_game();
        game.generate_out_to_file();
    }
}

void solve(int &board_num, string &in_path, int &game_num, int &difficulty, int &min_hole_num, int &max_hole_num, bool &is_unique){
    string out_path = "game.txt";
    Game game(board_num, in_path, out_path, difficulty, min_hole_num, max_hole_num, is_unique);
    game.in_from_file();
    game.solve_game();
    game.solve_out_to_file();
}

int main(int argc, char* argv[]){
    int board_num = 5;
    bool is_generate = true;
    string input_path = "game.txt";
    int game_num = 0;
    int difficulty = 0;
    int min_hole_num=0, max_hole_num=0;
    bool is_unique = false;

    extract_param(argc, argv, board_num, is_generate, input_path, game_num, difficulty, min_hole_num, max_hole_num, is_unique);
    if(!check_param(board_num, is_generate, input_path, game_num, difficulty, min_hole_num, max_hole_num, is_unique)){
        return 0;
    };
    set_uninitialized_param(board_num, is_generate, input_path, game_num, difficulty, min_hole_num, max_hole_num, is_unique);
    
    if(is_generate){
        generate(board_num, input_path, game_num, difficulty, min_hole_num, max_hole_num, is_unique);
    }else{
        solve(board_num, input_path, game_num, difficulty, min_hole_num, max_hole_num, is_unique);
    }
    return 0;
}