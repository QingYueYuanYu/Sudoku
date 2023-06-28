#include <vector>
#include "Cell.h"
using namespace std;

class Board{
private:
    Cell rows[9][9];
    Cell cols[9][9];
    Cell boxs[9][9];
    Cell cells[81];
    int difficulty;
    int hole_num;
    bool is_unique;
public:
    friend class Game;
    Board();
    Board(vector<int> values, int diff);
    void update_cell(Cell cell);
    vector<Cell> get_used_cells();
    vector<Cell> get_unused_cells();
    vector<int> get_possibilities(Cell cell);
    void set_difficulty(int diff);
    void set_hole_num(int hole_n);
    void set_unique(bool is_uni);
    void swap_row(int row1, int row2);
    void swap_col(int col1, int col2);
    void swap_stack(int stack1, int stack2);
    void swap_band(int band1, int band2);
    void shuffle(int iterations);
    void reduce_via_logical();
    void generate();
    bool solve();
    void reset_values(vector<int> values);
    void in_from_file(string path);
    void out_to_file(string path);
    void output();
};