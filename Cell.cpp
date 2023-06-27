#include "Cell.h"
using namespace std;

Cell::Cell(){
    row = 0;
    col = 0;
    box = 0;
    value = 0;
}

Cell::Cell(int r, int c, int b, int v){
    row = r;
    col = c;
    box = b;
    value = v;
}

void Cell::setCell(int r, int c, int b, int v){
    row = r;
    col = c;
    box = b;
    value = v;
}

void Cell::setValue(int v){
    value = v;
}

int Cell::getValue(){
    return value;
}