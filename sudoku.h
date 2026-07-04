#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include <stdlib.h>

int main();
int solve(int row, int column, int sudoku[9][9]); 
int validate_cell(int row, int column, int number, int sudoku[9][9]); // einzelnes Feld checken
int** read();
int validate(int** matrix); // ganzes Sudoku checken
void output(int** matrix);
void printMatrix(int** matrix);

#endif
