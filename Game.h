#include <vector>
#include <string>
#include "Board.h"
using namespace std;

class Game{
private:
    int board_num;
    vector<Board> boards;
    string path;
    int difficulty;
    int min_hole_num, max_hole_num;
    bool is_unique;
public:
    Game();
    Game(int board_n, string pat, int diff, int min_hole_n, int max_hole_n, bool is_uni);
    void generate_game();
    void out_to_file();
};