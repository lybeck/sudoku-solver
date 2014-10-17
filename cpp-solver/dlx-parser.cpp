
#include <iostream>

#include "dlx-parser.h"

namespace dlx {

    dlx_parser::dlx_parser(sudoku s, int n) : sudoku_(s), n_(n) {
        n2_ = n_ * n_;
        n4_ = n2_ * n2_;
        cols_ = 4 * n4_;
        columns_ = new column_node*[cols_];
        nodes_ = new node*[4];
        indices_ = new int[4];
    }

    dlx_parser::~dlx_parser() {
        delete columns_;
        delete indices_;
        delete nodes_;
    }

    column_node* dlx_parser::parse() {

#ifndef NDEBUG
        std::cout << "Parsing..." << std::endl;
#endif

        column_node* h = init_header();

        init_columns(h);

        add_rows();

        return h;
    }

    column_node* dlx_parser::init_header() {

#ifndef NDEBUG
        std::cout << "  init_header" << std::endl;
#endif
        column_node* h = new column_node();
        L(h) = h;
        R(h) = h;
        return h;
    }

    void dlx_parser::init_columns(column_node* h) {

#ifndef NDEBUG
        std::cout << "  init_columns" << std::endl;
#endif
        column_node* prev = h;
        column_node* curr;
        for (int i = 0; i < cols_; i++) {
            curr = new column_node();
            U(curr) = curr;
            D(curr) = curr;
            L(curr) = prev;
            R(prev) = curr;
            columns_[i] = curr;
            prev = curr;
        }
        R(prev) = h;
        L(h) = prev;
    }

    void dlx_parser::add_rows() {

#ifndef NDEBUG
        std::cout << "  add_rows" << std::endl;
#endif
        int num;
        for (int i = 0; i < n2_; i++) {
            for (int j = 0; j < n2_; j++) {
                num = get(sudoku_, n2_, i, j);
                if (num != 0) {
                    add_row(i, j, num);
                } else {
                    for (int k = 0; k < n2_; k++) {
                        add_row(i, j, k);
                    }
                }
            }
        }
    }

    void dlx_parser::add_row(int i, int j, int num) {
        setup_nodes(i, j, num);
        setup_indices(i, j, num);
        add_row_to_matrix();
    }

    void dlx_parser::setup_nodes(int i, int j, int num) {

        // create the nodes
        int index = get_index(n2_, i, j);
        for (int i = 0; i < 4; i++) {
            nodes_[i] = new node();
            V(nodes_[i]) = num;
            I(nodes_[i]) = index;
        }

        // link the nodes together
        node* prev = nodes_[0];
        node* curr;
        for (int k = 1; k < 4; k++) {
            curr = nodes_[k];
            L(curr) = prev;
            R(prev) = curr;
            prev = curr;
        }
        R(prev) = nodes_[0];
        L(nodes_[0]) = prev;
    }

    void dlx_parser::setup_indices(int i, int j, int num) {
        indices_[0] = 0 * n4_ + n2_ * i + j;
        indices_[1] = 1 * n4_ + n2_ * i + (num - 1);
        indices_[2] = 2 * n4_ + n2_ * j + (num - 1);
        indices_[3] = 3 * n4_ + n2_ * get_box_number(i, j) + (num - 1);
    }

    int dlx_parser::get_box_number(int i, int j) {
        int ib = i / n_;
        int jb = j / n_;
        return ib * n_ + jb;
    }

    void dlx_parser::add_row_to_matrix() {
        node* n;
        int index;
        column_node* c;
        for (int i = 0; i < 4; i++) {
            n = nodes_[i];
            index = indices_[i];
            c = columns_[index];
            D(U(c)) = n;
            U(n) = U(c);
            U(c) = n;
            D(n) = c;
            C(n) = c;
            ++S(c);
        }
    }
}
