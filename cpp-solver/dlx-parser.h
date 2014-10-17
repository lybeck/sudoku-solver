/* 
 * File:   dlx-parser.h
 * Author: Lasse Lybeck
 *
 * Created on October 17, 2014, 10:14 AM
 */

#ifndef DLX_PARSER_H
#define	DLX_PARSER_H

#include "column_node.h"
#include "sudoku.h"
#include "node.h"

namespace dlx {

    class dlx_parser {
    public:
        dlx_parser(sudoku, int);
        dlx_parser(dlx_parser const&) = delete;
        virtual ~dlx_parser();
        column_node* parse();
    private:
        sudoku sudoku_;
        int n_;
        int n2_;
        int n4_;
        int cols_;
        column_node** columns_;
        node** nodes_;
        int* indices_;

        column_node* init_header();
        void init_columns(column_node*);
        void add_rows();
        void add_row(int, int, int);
        void setup_nodes(int, int, int);
        void setup_indices(int, int, int);
        int get_box_number(int, int);
        void add_row_to_matrix();
    };


}

#endif	/* DLX_PARSER_H */

