/* 
 * File:   node.cpp
 * Author: Lasse Lybeck
 * 
 * Created on October 16, 2014, 12:38 PM
 */

#include "node.h"

namespace dlx {

    node::node() : left_(this), right_(this), up_(this), down_(this), column_(this), value_(0), index_(0) { }

    node::~node() { }

    node*& node::left() {
        return left_;
    }

    node*& node::right() {
        return right_;
    }

    node*& node::up() {
        return up_;
    }

    node*& node::down() {
        return down_;
    }

    node*& node::column() {
        return column_;
    }

    int& node::value() {
        return value_;
    }

    int& node::index() {
        return index_;
    }

    node*& L(node* n) {
        return n->left();
    }

    node*& R(node* n) {
        return n->right();
    }

    node*& U(node* n) {
        return n->up();
    }

    node*& D(node* n) {
        return n->down();
    }

    node*& C(node* n) {
        return n->column();
    }
    
    int& V(node* n) {
        return n->value();
    }
    
    int& I(node* n) {
        return n->index();
    }
}
