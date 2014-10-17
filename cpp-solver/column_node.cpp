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

    int& S(column_node* c) {
        return c->size();
    }
}
