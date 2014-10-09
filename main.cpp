/* 
 * File:   main.cpp
 * Author: Lasse Lybeck
 *
 * Created on October 9, 2014, 6:07 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "solver.h"

using namespace std;

inline sudoku read_sudoku(int* n) {
    cin >> *n;
    int nums = pow(*n, 4);
    int* sudoku = new int[nums];

    for (int i = 0; i < nums; i++) {
        cin >> sudoku[i];
    }

    return sudoku;
}

inline void print_sudoku(sudoku sudoku, int n) {
    int n2 = n*n;
    int n4 = n2*n2;
    for (int i = 0; i < n4; i++) {
        cout << sudoku[i];
        if ((i + 1) % n2)
            cout << " ";
        else
            cout << endl;
    }
}

int number_of_digits(int i) {
    int number_of_digits = 0;
    do {
        ++number_of_digits;
        i /= 10;
    } while (i);
    return number_of_digits;
}

inline void print_sudoku_readable(sudoku sudoku, int n) {
    int n2 = n*n;
    int n4 = n2*n2;
    int width = number_of_digits(n2);
    for (int i = 0; i < n4; i++) {
        cout << setw(width) << sudoku[i];
        if ((i + 1) % n2) {
            cout << " ";
            if (!((i + 1) % n)) {
                cout << " | ";
            }
        } else {
            cout << endl;
            if (!((i + 1) % (n * n2)) && i < n4 - 1) {
                for (int j = 0; j < n2; j++) {
                    for (int k = 0; k < width + 1; k++) {
                        cout << "-";
                    }
                    if (!((j + 1) % n) && j < n2 - 1) {
                        cout << "-+-";
                    }
                }
                cout << endl;
            }
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    int n;
    sudoku sudoku;

    sudoku = read_sudoku(&n);

    bool solved = solve(sudoku, n);

    if (solved) {
#ifdef NDEBUG
        print_sudoku(sudoku, n);
#else
        print_sudoku_readable(sudoku, n);
#endif
    } else {
        cout << "Impossible";
#ifndef NDEBUG
        print_sudoku_readable(sudoku, n);
#endif
    }

    delete sudoku;

    return 0;
}

