#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include <stdlib.h>

int solve(int row, int column, int **sudoku); 
int validate_cell(int row, int column, int number, int **sudoku); // einzelnes Feld checken
int** read(void);
int validate(int** matrix); // ganzes Sudoku checken
void output(int** matrix);

void printMatrix(int** matrix);
void printRow(int* row);
void printBox(int **matrix, int box);

void motivateMe(void);

int **createSudoku(int difficulty);
int getSolutionAmount(int **sudoku);
int DonaldKnuth(int **sudoku, int doASolve);
void playSudokuInteractive(int **sudoku);
int isSudokuFinished(int **sudoku);

void returnToMenu(void);
int getUserIntInput(int min, int max);

#endif
