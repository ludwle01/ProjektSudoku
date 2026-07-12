#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sudoku.h"

// ganzes Sudoku ausgeben
void printMatrix(int **matrix){
    for (int i = 0; i < SIZE; i++){
        printRow(matrix[i]); // Reihen ausgeben
        if((i+1)%BLOCK == 0 && i < SIZE -1){ // Trennstriche zwischen den Blöcken
            for(int j = 0; j < (SIZE+BLOCK-1)*2; j++){
                printf("-");               
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

//einzelne Zeile ausgeben
void printRow(int *row) {
    for (int i = 0; i < SIZE; i++) {
        printValue(row[i]);
        if ((i+1)%BLOCK == 0 && i < SIZE-1) {
            printf("| "); // Trennstriche für Blöcke
        }
    }
    printf("\n"); // Zeilenumbruch am Ende
}

//4*4 Box ausgeben
void printBox(int **matrix, int box) {
    int row = (int) (box-1)/BLOCK; // 0 oben, 1 mitte oben, 2 mitte unten, 3 unten
    int col = (box-1) % BLOCK; // 0 links, 1 mitte links, 2 mitte rechts, 3 rechts

    for (int i=0; i<BLOCK; i++) { // 4x4 Box durchgehen
      for(int j=0; j<BLOCK; j++){
        printValue(matrix[BLOCK*row+i][BLOCK*col+j]);
      }
      printf("\n");
    }
}

void printValue(int value) { // Ausgabe im Hexadezimal Format
    if (value == EMPTY) { // leeres Feld als . ausgeben
        printf(". ");
    } else if (value < 10) {
        printf("%d ", value);
    } else {
        printf("%c ", 'A' + value - 10);
    }
}