
#include <cstdlib>
#include <limits>
#include <map>
#include <set>
#include "dlx-parser.h"
#include "dlx-solver.h"
#include "node.h"
#include "column_node.h"

#ifndef NDEBUG
#include <iostream>
#endif

namespace dlx {

    typedef std::map<int, std::set<column_node*>* > map_type;
    typedef std::set<column_node*> set_type;

    dlx_solver::dlx_solver(sudoku s, int n) : sudoku_(s), solved_(false), n_(n), n2_(n*n), n4_(n2_*n2_) {

        o_ = new node*[n4_];

#ifndef NDEBUG
        std::cout << "dlx_solver::init" << std::endl;
#endif

        h_ = parse();

#ifndef NDEBUG
        std::cout << "Parsing done!" << std::endl;
#endif

        map_ = new map_type();
        all_sets_ = new map_type();
        for (column_node* c = R(h_); c != h_; c = R(c)) {
            add_to_map(c);
        }

#ifndef NDEBUG
        std::cout << "Map size: " << map_->size() << std::endl;
        for (map_type::iterator it = map_->begin(); it != map_->end(); ++it) {
            std::cout << it->first << " -> " << it->second->size() << std::endl;
        }
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
        return *(map_->begin()->second->begin());
    }

    void dlx_solver::cover_column(column_node* c) {
        remove_from_map(c);
        L(R(c)) = L(c);
        R(L(c)) = R(c);
        for (node* i = D(c); i != c; i = D(i)) {
            for (node* j = R(i); j != i; j = R(j)) {
                U(D(j)) = U(j);
                D(U(j)) = D(j);
                decrease_key(C(j));
            }
        }
    }

    void dlx_solver::uncover_column(column_node* c) {
        for (node* i = U(c); i != c; i = U(i)) {
            for (node* j = L(i); j != i; j = L(j)) {
                increase_key(C(j));
                U(D(j)) = j;
                D(U(j)) = j;
            }
        }
        L(R(c)) = c;
        R(L(c)) = c;
        add_to_map(c);
    }

    void dlx_solver::decrease_key(column_node* c) {
        remove_from_map(c);
        --S(c);
        add_to_map(c);
    }

    void dlx_solver::increase_key(column_node* c) {
        remove_from_map(c);
        ++S(c);
        add_to_map(c);
    }

    void dlx_solver::add_to_map(column_node* c) {
        if (map_->find(S(c)) == map_->end()) {
            if (all_sets_->find(S(c)) == all_sets_->end()) {
                (*all_sets_)[S(c)] = new set_type();
            }
            (*map_)[S(c)] = (*all_sets_)[S(c)];
        }
        (*map_)[S(c)]->insert(c);
    }

    void dlx_solver::remove_from_map(column_node* c) {
        set_type* set = (*map_)[S(c)];
        set->erase(c);
        if (set->empty()) {
            map_->erase(S(c));
        }
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

#ifndef NDEBUG
        std::cout << "Map size: " << map_->size() << std::endl;
        for (map_type::iterator it = map_->begin(); it != map_->end(); ++it) {
            std::cout << it->first << " -> " << it->second->size() << std::endl;
        }
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
