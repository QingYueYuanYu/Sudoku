#include <vector>
#include <string>
#include "Board.h"
using namespace std;

class Game{
private:
    int board_num;
    vector<Board> boards;
    string in_path, solve_out_path, generate_out_path;
    int difficulty;
    int min_hole_num, max_hole_num;
    bool is_unique;
public:
    Game();
    Game(int board_n, string in_pat, string out_pat, int diff, int min_hole_n, int max_hole_n, bool is_uni);
    void generate_game();
    void solve_game();
    void in_from_file();
    void out_to_file(string out_path);
    void generate_out_to_file();
    void solve_out_to_file();
};