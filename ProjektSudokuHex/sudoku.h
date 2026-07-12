#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include <stdlib.h>

#define SIZE 16
#define BLOCK 4
#define EMPTY -1

int main();
int solve(int row, int column, int **sudoku); 
int validate_cell(int row, int column, int number, int **sudoku); // einzelnes Feld checken
int** read();

void printMatrix(int** matrix);
void printRow(int* row);
void printBox(int **matrix, int box);
void printValue(int value);

void motivateMe();

#endif
