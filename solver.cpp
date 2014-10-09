
#include "solver.h"

#include <iostream>

using namespace std;

sudoku _sudoku;

int n;
int n2;
int n4;

int* last;
bool* constant;

inline int get(int i, int j) {
    return _sudoku[i * n2 + j];
}

bool solve(sudoku s, int N) {
    
    _sudoku = s;
    
    n = N;
    n2 = n*n;
    n4 = n2*n2;

    last = new int[n4]();
    constant = new bool[n4];
    for (int i = 0; i < n4; i++) {
        constant[i] = (_sudoku[i] != 0);
    }

    return true;
}
