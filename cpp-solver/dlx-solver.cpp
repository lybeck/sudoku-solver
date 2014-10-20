
#include <cstdlib>
#include <limits>
#include "dlx-parser.h"
#include "dlx-solver.h"
#include "node.h"
#include "column_node.h"

#ifndef NDEBUG
#include <iostream>
#endif

namespace dlx {

    dlx_solver::dlx_solver(sudoku s, int n) : sudoku_(s), solved_(false), n_(n), n2_(n*n), n4_(n2_*n2_) {

        o_ = new node*[n4_];

#ifndef NDEBUG
        std::cout << "dlx_solver::init" << std::endl;
#endif

        h_ = parse();

#ifndef NDEBUG
        std::cout << "Parsing done!" << std::endl;
#endif

    }

    dlx_solver::~dlx_solver() {
        delete o_;
        // TODO: should also delete all the nodes starting from the header..
    }

    column_node* dlx_solver::parse() {
        dlx_parser parser(sudoku_, n_);
        return parser.parse();
    }

    bool dlx_solver::solve() {

#ifndef NDEBUG
        std::cout << "Solving..." << std::endl;
#endif

        search(0);

#ifndef NDEBUG
        std::cout << "Search done!" << std::endl;
#endif

        return solved_;
    }

    void dlx_solver::search(int k) {

#ifndef NDEBUG
        //        std::cout << "k = " << k << std::endl;
#endif

        if (R(h_) == h_) {

#ifndef NDEBUG
            std::cout << "Solution found!" << std::endl;
#endif

            solved_ = true;
            set_solution();
            return;
        }

        column_node* c = select_column();

        cover_column(c);
        for (node* r = D(c); r != c; r = D(r)) {
            o_[k] = r;
            for (node* j = R(r); j != r; j = R(j)) {
                cover_column(C(j));
            }

            search(k + 1);

            r = o_[k];
            for (node* j = L(r); j != r; j = L(j)) {
                uncover_column(C(j));
            }

            if (solved_) {
                break;
            }
        }
        uncover_column(c);
    }

    column_node* dlx_solver::select_column() {

        column_node* c;
        int s = std::numeric_limits<int>::max();
        for (column_node* j = R(h_); j != h_; j = R(j)) {
            if (S(j) < s) {
                c = j;
                s = S(j);
            }

            // This can be used as long as we can assume that we have a solution, else it should be removed!
            if (s <= 1) {
                return c;
            }
        }

        return c;
    }

    void dlx_solver::cover_column(column_node* c) {
        L(R(c)) = L(c);
        R(L(c)) = R(c);
        for (node* i = D(c); i != c; i = D(i)) {
            for (node* j = R(i); j != i; j = R(j)) {
                U(D(j)) = U(j);
                D(U(j)) = D(j);
                --S(C(j));
            }
        }
    }

    void dlx_solver::uncover_column(column_node* c) {
        for (node* i = U(c); i != c; i = U(i)) {
            for (node* j = L(i); j != i; j = L(j)) {
                ++S(C(j));
                U(D(j)) = j;
                D(U(j)) = j;
            }
        }
        L(R(c)) = c;
        R(L(c)) = c;
    }

    void dlx_solver::set_solution() {
#ifndef NDEBUG
        std::cout << "Setting solution." << std::endl;
#endif
        node* nd;
        int i, j;
        for (int k = 0; k < n4_; k++) {
            nd = o_[k];
            get_coords(n2_, I(nd), &i, &j);
            get(sudoku_, n2_, i, j) = V(nd);
        }

#ifndef NDEBUG
        std::cout << "Solutions set." << std::endl;
#endif
    }

    void dlx_solver::debug_print_sizes() {
#ifndef NDEBUG
        for (column_node* j = R(h_); j != h_; j = R(j)) {
            std::cout << "  S(j) = " << S(j) << std::endl;
        }
#endif
    }

}
