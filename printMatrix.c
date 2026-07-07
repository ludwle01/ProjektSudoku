#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sudoku.h"

// ganzes Sudoku ausgeben
void printMatrix(int **matrix)
{
    // Counter, dass das Programm weiß, wann es Trennstriche augeben muss
    int counter = 0;
    int verschiebung = 0; // Zeilen counter geht auch bei "----" hoch -> i geht auch hoch -> matrix[i] muss angepasst werden
    // Verschachtelte for Schleife
    for (int i = 0; i < 11; i++)
    {
        if (counter == 3 || counter == 7)
        {
            printf("-------------------------------\n");
            counter++;
            verschiebung++;
        }
        else
        {
            printf(" %d  %d  %d |  %d  %d  %d |  %d  %d  %d\n", matrix[i - verschiebung][0], matrix[i - verschiebung][1], matrix[i - verschiebung][2], matrix[i - verschiebung][3], matrix[i - verschiebung][4], matrix[i - verschiebung][5], matrix[i - verschiebung][6], matrix[i - verschiebung][7], matrix[i - verschiebung][8]);
            counter++;
        }
    }
}

//einzelne Zeile ausgeben
void printRow(int *row) {
    for (int i = 0; i < 9; i++) {
        printf("%d ", row[i]);
        if (i==2||i==5) {
            printf("| "); // Trennstriche für Blöcke
        }
    }
    printf("\n"); // Zeilenumbruch am Ende
}

//3x3 Box ausgeben
void printBox(int **matrix, int box) {
    int row = (int) (box-1)/3; // 0 oben, 1 mitte, 2 unten
    int col = (box-1) % 3; // 0 links, 1 mitte, 2 rechts

    for (int i=0; i<3; i++) { // 3x3 Box durchgehen
      for(int j=0; j<3; j++){
        printf("%d ", matrix[3*row+i][3*col+j]);
      }
      printf("\n");
    }
}