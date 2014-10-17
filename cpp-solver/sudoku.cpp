
#include "sudoku.h"

void get_coords(int n2, int index, int* i, int* j) {
    *i = index / n2;
    *j = index % n2;
}

int get_index(int n2, int i, int j) {
    return i * n2 + j;
}

int& get(sudoku s, int n2, int i, int j) {
    return s[get_index(n2, i, j)];
}
