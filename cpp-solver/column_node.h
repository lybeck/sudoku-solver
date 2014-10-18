/* 
 * File:   column.h
 * Author: Lasse Lybeck
 *
 * Created on October 16, 2014, 12:46 PM
 */

#ifndef COLUMN_H
#define	COLUMN_H

#include <string>
#include "node.h"

namespace dlx {

    class column_node : public node {
    public:
        column_node();
        column_node(const column_node& orig) = delete;
        int& size();
        column_node*& right();
        column_node*& left();
    private:
        int size_;
    };

    int& S(column_node*);
    column_node*& R(column_node*);
    column_node*& L(column_node*);
    column_node*& C(node*);
}

#endif	/* COLUMN_H */

