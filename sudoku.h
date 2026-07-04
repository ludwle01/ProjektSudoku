#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include <stdlib.h>

int main();
int solve(int row, int column, int sudoku[9][9]); 
int validate_cell(int row, int column, int number, int sudoku[9][9]);
int** read();
int validate_matrix(int** matrix);
void output(int** matrix);
void printMatrix(int** matrix);

#endif
