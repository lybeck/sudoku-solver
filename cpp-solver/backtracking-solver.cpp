
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include "io.h"
#include "backtracking-solver.h"

namespace bt_solver {

    sudoku _sudoku;

    int n;
    int n2;
    int n4;

    int* _last;
    bool* _constant;
    bool* _check;
    int* _vals;

    unsigned seed;
    std::mt19937_64 rng;

    inline int* random_vals() {
        _vals = new int[n2];
        for (int i = 0; i < n2; i++) {
            _vals[i] = i + 1;
        }
        std::shuffle(_vals, _vals + n2, rng);
        return _vals;
    }

    inline void shuffle_sudoku(int shuffles) {
        int tmp[n4];
        unsigned long offset = n4 - shuffles * n * n2;
        unsigned long offset_end = n4 - offset;
        std::copy(_sudoku + offset, _sudoku + n4, tmp);
        std::copy(_sudoku, _sudoku + offset, tmp + offset_end);
        std::copy(tmp, tmp + n4, _sudoku);
    }

    inline void unshuffle_sudoku(int shuffles) {
        int tmp[n4];
        unsigned long offset = shuffles * n*n2;
        unsigned long offset_end = n4 - offset;
        std::copy(_sudoku + offset, _sudoku + n4, tmp);
        std::copy(_sudoku, _sudoku + offset, tmp + offset_end);
        std::copy(tmp, tmp + n4, _sudoku);
    }

    inline int& get(int i, int j) {
        return _sudoku[i * n2 + j];
    }

    inline bool constant(int i, int j) {
        return _constant[i * n2 + j];
    }

    inline int& last(int i, int j) {
        return _last[i * n2 + j];
    }

    inline void reset_check() {
        std::fill_n(_check + 1, n2, false);
    }

    inline int box_corner(int i, int j, int* ii, int* jj) {
        *ii = n * (i / n);
        *jj = n * (j / n);
    }

    inline bool row_ok(int r) {
        reset_check();
        for (int i = 0; i < n2; i++) {
            int v = get(r, i);
            if (v == 0)
                continue;
            if (_check[v])
                return false;
            _check[v] = true;
        }
        return true;
    }

    inline bool col_ok(int c) {
        reset_check();
        for (int i = 0; i < n2; i++) {
            int v = get(i, c);
            if (v == 0)
                continue;
            if (_check[v])
                return false;
            _check[v] = true;
        }
        return true;
    }

    inline bool box_ok(int bi, int bj) {
        reset_check();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int v = get(bi + i, bj + j);
                if (v == 0)
                    continue;
                if (_check[v])
                    return false;
                _check[v] = true;
            }
        }
        return true;
    }

    inline bool ok(int i, int j) {
        int bi;
        int bj;
        box_corner(i, j, &bi, &bj);
        return row_ok(i) && col_ok(j) && box_ok(bi, bj);
    }

    inline void next(int* i, int* j) {
        if (++(*j) == n2) {
            ++(*i);
            *j = 0;
        }
    }

    inline void prev(int* i, int* j) {
        if (--(*j) == -1) {
            --(*i);
            *j = n2;
        }
    }

    bool solve() {

        int i = 0;
        int j = 0;
        int ind;
        bool continue_loop = false;

        while (true) {
            if (i == n2)
                return true;
            if (i < 0)
                return false;

            if (constant(i, j)) {
                next(&i, &j);
                continue;
            }

            do {
                ind = last(i, j)++;
                if (ind == n2) {
                    last(i, j) = 0;
                    get(i, j) = 0;
                    do {
                        prev(&i, &j);
                    } while (constant(i, j));
                    continue_loop = true;
                    break;
                } else {
                    get(i, j) = _vals[ind];
                }
            } while (!ok(i, j));
            if (continue_loop) {
                continue_loop = false;
                continue;
            }

            next(&i, &j);
        }


        return true;
    }

    bool solve(sudoku s, int N) {

        _sudoku = s;

        n = N;
        n2 = n*n;
        n4 = n2*n2;

        seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng.seed(seed);
        int shuffles = (rng() % (n - 1)) + 1;

        shuffle_sudoku(shuffles);

#ifndef NDEBUG
        std::cout << "Shuffled:" << std::endl;
        print_sudoku_readable(_sudoku, n);
#endif

        _last = new int[n4]();
        _constant = new bool[n4];
        _check = new bool[n2 + 1];
        _vals = random_vals();
        for (int i = 0; i < n4; i++) {
            _constant[i] = (_sudoku[i] != 0);
        }

        bool solved = solve();

        delete _last;
        delete _constant;
        delete _check;
        delete _vals;

        unshuffle_sudoku(shuffles);

        return solved;
    }

}
