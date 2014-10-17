/* 
 * File:   sudoku.h
 * Author: Lasse Lybeck
 *
 * Created on October 16, 2014, 2:52 PM
 */

#ifndef SUDOKU_H
#define	SUDOKU_H


typedef int* sudoku;

int& get(sudoku, int n2, int i, int j);

int get_index(int n2, int i, int j);

void get_coords(int n2, int index, int* i, int* j);


#endif	/* SUDOKU_H */

