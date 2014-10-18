/* 
 * File:   column.cpp
 * Author: Lasse Lybeck
 * 
 * Created on October 16, 2014, 12:46 PM
 */

#include "column_node.h"

namespace dlx {

    column_node::column_node() : size_(0) { }

    int& column_node::size() {
        return size_;
    }

    column_node*& column_node::right() {
        return (column_node*&) node::right();
    }

    column_node*& column_node::left() {
        return (column_node*&) node::left();
    }

    int& S(column_node* c) {
        return c->size();
    }

    column_node*& R(column_node* c) {
        return c->right();
    }

    column_node*& L(column_node* c) {
        return c->left();
    }

    column_node*& C(node* n) {
        return (column_node*&) n->column();
    }
}
