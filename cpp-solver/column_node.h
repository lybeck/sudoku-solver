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

    class column_node : node {
    public:
        column_node();
        column_node(const column_node& orig) = delete;
        virtual ~column_node();
        int& size();
        std::string& name();
    private:
        int size_;
        std::string name_;
    };

    int& S(column_node&);
    std::string& N(column_node&);
}

#endif	/* COLUMN_H */

