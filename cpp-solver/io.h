/* 
 * File:   io.h
 * Author: Lasse Lybeck
 *
 * Created on October 10, 2014, 12:47 PM
 */

#include "backtracking-solver.h"

#ifndef IO_H
#define	IO_H

sudoku read_sudoku(const char*, int*);

void print_sudoku(sudoku, int);

void print_sudoku_readable(sudoku, int);

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

