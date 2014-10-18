/* 
 * File:   dlx-solver.h
 * Author: Lasse Lybeck
 *
 * Created on October 16, 2014, 2:50 PM
 */

#ifndef DLX_SOLVER_H
#define	DLX_SOLVER_H

#include "sudoku.h"
#include "column_node.h"

namespace dlx {

    class dlx_solver {
    public:
        dlx_solver(sudoku, int);
        dlx_solver(dlx_solver const&) = delete;
        virtual ~dlx_solver();
        bool solve();
    private:
        sudoku sudoku_;
        bool solved_;
        int n_;
        int n2_;
        int n4_;
        node** o_;
        column_node* h_;
        
        column_node* parse();
        void search(int);
        column_node* select_column();
        void cover_column(column_node*);
        void uncover_column(column_node*);
        void set_solution();
        void debug_print_sizes();
    };
}

#endif	/* DLX_SOLVER_H */

