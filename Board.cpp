#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include "Board.h"
using namespace std;

Board::Board(){
    // cout<<"-----Begin Board()-----"<<endl;
    vector<int> values;
    ifstream f("base.txt");
    string line;
    while(getline(f, line)){
        stringstream f_line(line);
        int value;
        while(f_line>>value){
            values.push_back(value);
        }
    }

    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            int box = 3*(row/3) + col/3;
            Cell cell = Cell(row, col, box, values[row*9+col]);
            rows[row][col] = cell;
            cols[col][row] = cell;
            boxs[box][3*(row%3)+col%3] = cell;
            cells[row*9+col] = cell;
        }
    }
    difficulty = 0;
    hole_num = 10;
    is_unique = false;
}

Board::Board(vector<int> values, int diff){
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            int box = 3*(row/3) + col/3;
            Cell cell = Cell(row, col, box, values[row*9+col]);
            rows[row][col] = cell;
            cols[col][row] = cell;
            boxs[box][3*(row%3)+col%3] = cell;
            cells[row*9+col] = cell;
        }
    }
    difficulty = diff;
}

void Board::update_cell(Cell cell){
    rows[cell.row][cell.col] = cell;
    cols[cell.col][cell.row] = cell;
    boxs[cell.box][3*(cell.row%3)+cell.col%3] = cell;
    cells[cell.row*9+cell.col] = cell;
}

vector<Cell> Board::get_used_cells(){
    vector<Cell> used_cells;
    for(int idx=0; idx<81; idx++){
        if(cells[idx].getValue() != 0){
            used_cells.push_back(cells[idx]);
        }
    }
    return used_cells;
}

vector<Cell> Board::get_unused_cells(){
    vector<Cell> unused_cells;
    for(int idx=0; idx<81; idx++){
        if(cells[idx].getValue() == 0){
            unused_cells.push_back(cells[idx]);
        }
    }
    return unused_cells;
}

vector<int> Board::get_possibilities(Cell cell){
    vector<int> possibilities;
    vector<int> rows_values, cols_values, boxs_values;
    int tmp = rows[cell.row][cell.col].value;
    rows[cell.row][cell.col].value = 0;
    cols[cell.col][cell.row].value = 0;
    boxs[cell.box][3*(cell.row%3)+cell.col%3].value = 0;
    cells[cell.row*9+cell.col].value = 0;
    for(int idx=0; idx<9; idx++){
        rows_values.push_back(rows[cell.row][idx].getValue());
        cols_values.push_back(cols[cell.col][idx].getValue());
        boxs_values.push_back(boxs[cell.box][idx].getValue());
    }
    for(int value=1; value<10; value++){
        if(find(rows_values.begin(), rows_values.end(), value)==rows_values.end() && 
        find(cols_values.begin(), cols_values.end(), value)==cols_values.end() &&
        find(boxs_values.begin(), boxs_values.end(), value)==boxs_values.end()){
            possibilities.push_back(value);
        }
    }
    rows[cell.row][cell.col].value = tmp;
    cols[cell.col][cell.row].value = tmp;
    boxs[cell.box][3*(cell.row%3)+cell.col%3].value = tmp;
    cells[cell.row*9+cell.col].value = tmp;
    return possibilities;
}

void Board::set_difficulty(int diff){
    difficulty = diff;
}

void Board::set_hole_num(int hole_n){
    hole_num = hole_n;
}

void Board::set_unique(bool is_uni){
    is_unique = is_uni;
}

void Board::swap_row(int row1, int row2){
    for(int col=0; col<9; col++){
        int tmp = rows[row1][col].value;
        rows[row1][col].value = rows[row2][col].value;
        rows[row2][col].value = tmp;
        cols[col][row1].value = cols[col][row2].value;
        cols[col][row2].value = tmp;
        boxs[3*(row1/3)+col/3][3*(row1%3)+col%3].value = boxs[3*(row2/3)+col/3][3*(row2%3)+col%3].value;
        boxs[3*(row2/3)+col/3][3*(row2%3)+col%3].value = tmp;
        cells[row1*9+col].value = cells[row2*9+col].value;
        cells[row2*9+col].value = tmp;
    }
}

void Board::swap_col(int col1, int col2){
    for(int row=0; row<9; row++){
        int tmp = rows[row][col1].value;
        rows[row][col1].value = rows[row][col2].value;
        rows[row][col2].value = tmp;
        cols[col1][row].value = cols[col2][row].value;
        cols[col2][row].value = tmp;
        boxs[3*(row/3)+col1/3][3*(row%3)+col1%3].value = boxs[3*(row/3)+col2/3][3*(row%3)+col2%3].value;
        boxs[3*(row/3)+col2/3][3*(row%3)+col2%3].value = tmp;
        cells[row*9+col1].value = cells[row*9+col2].value;
        cells[row*9+col2].value = tmp;
    }
}

void Board::swap_stack(int stack1, int stack2){
    for(int idx=0; idx<3; idx++){
        swap_col(stack1*3+idx, stack2*3+idx);
    }
}

void Board::swap_band(int band1, int band2){
    for(int idx=0; idx<3; idx++){
        swap_row(band1*3+idx, band2*3+idx);
    }
}

void Board::shuffle(int iterations){
    for(int iter=0; iter<iterations; iter++){
        srand((unsigned)time(NULL)*iter); 
        // cout<<"time: "<<(unsigned)time(NULL)<<endl;
        int tmp=0;
        int kind = rand()%4;
        int block = rand()%2 * 3;
        int piece1 = rand()%3;
        int piece2 = rand()%3;
        while(piece2==piece1){
            srand((unsigned)time(NULL)*iter+tmp); 
            piece2 = rand()%3;
            tmp ++;
        }
        // cout<<"kind: "<<kind<<" "<<"block:"<<block<<" "<<"piece1: "<<piece1<<" "<<"piece2: "<<piece2<<endl;
        if(kind == 0){
            swap_row(block+piece1, block+piece2);
        }else if(kind == 1){
            swap_col(block+piece1, block+piece2);
        }else if(kind == 2){
            swap_stack(piece1, piece2);
        }else{
            swap_band(piece1, piece2);
        }
        // cout<<"Finish iter: "<<iter<<" of "<<iterations<<endl;
    }
}

void Board::reduce_via_logical(){
    int counter = 0;
    int tmp = 0;
    vector<Cell> used_cells = get_used_cells();
    vector<int> shuffle_used_cells_idx;
    vector<Cell> shuffle_used_cells;
    while(shuffle_used_cells_idx.size()<used_cells.size()){
        tmp ++;
        srand((unsigned)time(NULL)+tmp); 
        int idx = rand()%used_cells.size();
        if(find(shuffle_used_cells_idx.begin(), shuffle_used_cells_idx.end(), idx) == shuffle_used_cells_idx.end()){
            shuffle_used_cells_idx.push_back(idx);
        }
    }
    for(int idx=0; idx<int(shuffle_used_cells_idx.size()); idx++){
        shuffle_used_cells.push_back(used_cells[shuffle_used_cells_idx[idx]]);
    }
    // cout<<"shuffle_used_cells size: "<<shuffle_used_cells.size()<<endl;
    for(int idx=0; idx<int(shuffle_used_cells.size()); idx++){
        vector<int> possibilities = get_possibilities(shuffle_used_cells[idx]);
        if(counter == hole_num){
            break;
        }
        // cout<<"possibilities size: "<<possibilities.size()<<endl;
        if(is_unique){
            if(possibilities.size() == 1){
                Cell cell = shuffle_used_cells[idx];
                rows[cell.row][cell.col].value = 0;
                cols[cell.col][cell.row].value = 0;
                boxs[cell.box][3*(cell.row%3)+cell.col%3].value = 0;
                cells[cell.row*9+cell.col].value = 0;
                counter ++;
                // cout<<"Modify: ("<<cell.row<<","<<cell.col<<")"<<endl;
            }
        }else{
            if(possibilities.size()>=1 && possibilities.size()<=10-2*difficulty){
                Cell cell = shuffle_used_cells[idx];
                rows[cell.row][cell.col].value = 0;
                cols[cell.col][cell.row].value = 0;
                boxs[cell.box][3*(cell.row%3)+cell.col%3].value = 0;
                cells[cell.row*9+cell.col].value = 0;
                counter ++;
                // cout<<"Modify: ("<<cell.row<<","<<cell.col<<")"<<endl;
            }
        }
    }
}

void Board::generate(){
    // cout<<"----------Begin Generate----------"<<endl;
    shuffle(10);
    // cout<<"-----After shuffle-----"<<endl;
    // output();
    reduce_via_logical();
    // cout<<"-----After reduce-----"<<endl;

}

void Board::out_to_file(string path){
    fstream f;
    f.open(path, ios::in);
    if(!f){
        f.open(path, ios::out);
    }
    f.seekp(0, ios::end);
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            if(cells[row*9+col].value==0){
                f<<"$"<<" ";
            }else{
                f<<cells[row*9+col].value<<" ";
            }
        }
        f<<"\n";
    }
    f.close();
    output();
    cout<<"----------"<<endl;
}

void Board::output(){
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            cout<<cells[row*9+col].value<<" ";
        }
        cout<<endl;
    }
}