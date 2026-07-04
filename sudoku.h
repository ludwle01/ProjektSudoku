#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>

// extern int grid[9][9];

// int solve();            //Solver
int is_valid(int **grid, int row, int column, int number); // Validierung für Solver
int **read();                                              // liest Sudokus aus Textdatei ein
int validate(int **matrix);                                // validiert Sudokus (eine doppelten Zahlen)
void output(int **matrix);                                 // Schreibt das übergene Sudoku in eine Textdatei
void printMatrix(int **matrix);                            // gibt Matrizen aus

#endif