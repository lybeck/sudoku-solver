
#include <cstdlib>
#include <iostream>
#include "dlx-parser.h"
#include "dlx-solver.h"
#include "node.h"
#include "column_node.h"

namespace dlx_solver {
    
    bool solved = false;
    
    dlx::column_node* parse(sudoku s, int n) {
        dlx::dlx_parser parser(s, n);
        return parser.parse();
    }

    bool solve(sudoku s, int n) {

        dlx::column_node* h = parse(s, n);
        
#ifndef NDEBUG
        std::cout << "Parsed!" << std::endl;
#endif
        
        return true;
    }

}
