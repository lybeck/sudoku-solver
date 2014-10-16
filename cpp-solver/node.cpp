/* 
 * File:   node.cpp
 * Author: Lasse Lybeck
 * 
 * Created on October 16, 2014, 12:38 PM
 */

#include "node.h"

namespace dlx {

    node::node() : left_(*this), right_(*this), up_(*this), down_(*this), column_(*this) { }

    node::node(node& col) : left_(*this), right_(*this), up_(*this), down_(*this), column_(col) { }

    node::~node() { }

    node& node::left() {
        return left_;
    }

    node& node::right() {
        return right_;
    }

    node& node::up() {
        return up_;
    }

    node& node::down() {
        return down_;
    }

    node& node::column() {
        return column_;
    }

    node& L(node& n) {
        return n.left();
    }
    
    node& R(node& n) {
        return n.left();
    }
    
    node& U(node& n) {
        return n.up();
    }
    
    node& D(node& n){
        return n.down();
    }
    
    node& C(node& n) {
        return n.column();
    }
}
