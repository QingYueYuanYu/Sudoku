using namespace std;
// 单元格类
class Cell {
private:
    int row, col, box, value;
public:
    friend class Board;
    Cell();
    Cell(int r, int c, int b, int v);
    void setCell(int r, int c, int b, int v);
    void setValue(int v);
    int getValue();
    Cell& operator=(const Cell& cell){
        row = cell.row;
        col = cell.col;
        box = cell.box;
        value = cell.value;
        return *this;
    }
    bool operator==(const Cell& cell){
        if(row==cell.row && col==cell.col && box==cell.box && value==cell.value){
            return true;
        }else{
            return false;
        }
    }
};