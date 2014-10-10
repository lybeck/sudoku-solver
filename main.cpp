/* 
 * File:   main.cpp
 * Author: Lasse Lybeck
 *
 * Created on October 9, 2014, 6:07 PM
 */

#include <cstdlib>
#include <iostream>
#include "io.h"
#include "solver.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int n;
    sudoku sudoku;

    sudoku = read_sudoku(&n);
    
#ifndef NDEBUG
    cout << endl << "Input: " << endl;
    print_sudoku_readable(sudoku, n);
    cout << endl;
#endif

    bool solved = solve(sudoku, n);

    if (solved) {
#ifdef NDEBUG
        print_sudoku(sudoku, n);
#else
        cout << endl << "Result:" << endl;
        print_sudoku_readable(sudoku, n);
        cout << endl;
#endif
    } else {
        cout << "Impossible" << endl;
#ifndef NDEBUG
        print_sudoku_readable(sudoku, n);
#endif
    }

    delete sudoku;

    return 0;
}

