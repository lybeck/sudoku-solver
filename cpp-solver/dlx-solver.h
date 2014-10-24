/* 
 * File:   dlx-solver.h
 * Author: Lasse Lybeck
 *
 * Created on October 16, 2014, 2:50 PM
 */

#ifndef DLX_SOLVER_H
#define	DLX_SOLVER_H

#include <map>
#include <set>

#include "sudoku.h"
#include "column_node.h"

#ifndef NDEBUG
#include "file_writer.h"
#endif

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
        
        std::map<int, std::set<column_node*>* > * map_;
        std::map<int, std::set<column_node*>* > * all_sets_;
        
#ifndef NDEBUG
        file_writer* file_;
#endif
        
        column_node* parse();
        void search(int);
        column_node* select_column();
        void cover_column(column_node*);
        void uncover_column(column_node*);
        void add_to_map(column_node*);
        void remove_from_map(column_node*);
        void increase_key(column_node*);
        void decrease_key(column_node*);
        void set_solution();
        void debug_print_sizes();
    };
}

#endif	/* DLX_SOLVER_H */

