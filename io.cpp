
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "io.h"
#include "solver.h"

inline int number_of_digits(int i) {
    int number_of_digits = 0;
    do {
        ++number_of_digits;
        i /= 10;
    } while (i);
    return number_of_digits;
}

sudoku read_sudoku(int* n) {
    std::cin >> *n;
    int nums = pow(*n, 4);
    int* sudoku = new int[nums];

    for (int i = 0; i < nums; i++) {
        std::cin >> sudoku[i];
    }

    return sudoku;
}

void print_sudoku(sudoku _sudoku, int n) {
    int n2 = n*n;
    int n4 = n2*n2;
    for (int i = 0; i < n4; i++) {
        std::cout << _sudoku[i];
        if ((i + 1) % n2)
            std::cout << " ";
        else
            std::cout << std::endl;
    }
}

void print_sudoku_readable(sudoku _sudoku, int n) {
    int n2 = n*n;
    int n4 = n2*n2;
    int width = number_of_digits(n2);
    for (int i = 0; i < n4; i++) {
        std::cout << std::setw(width) << _sudoku[i];
        if ((i + 1) % n2) {
            std::cout << " ";
            if (!((i + 1) % n)) {
                std::cout << " | ";
            }
        } else {
            std::cout << std::endl;
            if (!((i + 1) % (n * n2)) && i < n4 - 1) {
                for (int j = 0; j < n2; j++) {
                    for (int k = 0; k < width + 1; k++) {
                        std::cout << "-";
                    }
                    if (!((j + 1) % n) && j < n2 - 1) {
                        std::cout << "-+-";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}
