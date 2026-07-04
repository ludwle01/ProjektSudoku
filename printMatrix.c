#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

void printMatrix(int **matrix)
{
    int counter = 0;
    int verschiebung = 0; // Stellt sicher, dass wir die richtige Zeile der int** matrix auslesen
    for (int i = 0; i < 11; i++)
    {
        if (counter == 3 || counter == 7)
        {
            printf("-------------------------------\n");
            counter++;
            verschiebung++; //
        }
        else
        {
            printf(" %d  %d  %d |  %d  %d  %d |  %d  %d  %d\n", matrix[i - verschiebung][0], matrix[i - verschiebung][1], matrix[i - verschiebung][2], matrix[i - verschiebung][3], matrix[i - verschiebung][4], matrix[i - verschiebung][5], matrix[i - verschiebung][6], matrix[i - verschiebung][7], matrix[i - verschiebung][8]);
            counter++;
        }
    }
}