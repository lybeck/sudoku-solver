/* 
 * File:   main.cpp
 * Author: Lasse Lybeck
 *
 * Created on October 9, 2014, 6:07 PM
 */

#include <cstdlib>
#include <ios>
#include <iostream>
#include "dlx-solver.h"
#include "io.h"
#include "backtracking-solver.h"
#include "sudoku.h"

using namespace std;

const int bt_threshold = 0;

inline bool solve_sudoku(sudoku s, int n) {

#ifndef NDEBUG
    cout << "n = " << n << endl;
#endif

    if (n <= bt_threshold) {
#ifndef NDEBUG
        cout << "Chose backtracking solver." << endl << endl;
#endif
        return bt_solver::solve(s, n);
    } else {
#ifndef NDEBUG
        cout << "Chose dlx solver." << endl << endl;
#endif
        return dlx_solver::solve(s, n);
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    if (argc != 2) {
        cerr << "No input file as runtime argument! Exiting." << std::endl;
        return 1;
    }

#ifdef NDEBUG
    ios::sync_with_stdio(false);
#endif

    int n;
    sudoku s;

    s = read_sudoku(argv[1], &n);

#ifndef NDEBUG
    cout << endl << "Input: " << endl;
    print_sudoku_readable(s, n);
    cout << endl;
#endif

    bool solved = solve_sudoku(s, n);

    if (solved) {
#ifdef NDEBUG
        print_sudoku(s, n);
#else
        cout << endl << "Result:" << endl;
        print_sudoku_readable(s, n);
        cout << endl;
#endif
    } else {
        cout << "Impossible" << endl;
#ifndef NDEBUG
        print_sudoku_readable(s, n);
#endif
    }

    delete s;

    return 0;
}

