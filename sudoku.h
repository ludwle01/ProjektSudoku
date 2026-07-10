#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include <stdlib.h>

int main();
int solve(int row, int column, int **sudoku); 
int validate_cell(int row, int column, int number, int **sudoku); // einzelnes Feld checken
int** read();
int validate(int** matrix); // ganzes Sudoku checken
void output(int** matrix);

void printMatrix(int** matrix);
void printRow(int* row);
void printBox(int **matrix, int box);


void motivateMe();

#endif
