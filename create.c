#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

// Sinn dieser Funktion: Brute Force für das Erstellen eines Sudokus. Dieses wird in createSudoku.txt ausgegeben.

int **createSudoku(int difficulty)
{
    // Je mehr Zahlen entfernt werden, desto schwieriger wird das Sudoku
    int numbersToBeRemoved;

    if (difficulty == 1)
    {
        numbersToBeRemoved = 40;
    }
    else if (difficulty == 2)
    {
        numbersToBeRemoved = 50;
    }
    else
    {
        numbersToBeRemoved = 55;
    }

    // Ein Sudoku erstellen
    int **sudoku = (int **)malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; i++)
    {
        sudoku[i] = (int *)calloc(9, sizeof(int));
    }

    // Zufällige Zahlen in das Sudoku eintragen, um jedes Mal ein anderes Sukoku zu kriegen
    for (int i = 0; i < 2; i++)
    {
        int row = rand() % 9;
        int col = rand() % 9;
        int num = (rand() % 9) + 1;
        sudoku[row][col] = num;
    }

    // Überprüfen ob das Sudoku valide ist, ansonsten wird ein Neues erstellt
    int isValid = DonaldKnuth(sudoku, 1);

    if (isValid == 0)
    {
        // sicherheitsnetz, um Endlosschleifen zu vermeiden
        int attemptsTried = 0;

        // Nun sollen zufällige Zahlen entfernt werden
        for (int i = 0; i < numbersToBeRemoved; i++)
        {
            int row = rand() % 9;
            int col = rand() % 9;
            int temp = sudoku[row][col];

            // Feld wird leer gemacht, ansonsten wird die Iteration wiederholt
            if (sudoku[row][col] != 0)
            {
                sudoku[row][col] = 0;

                // Überprüfen, ob das Sudoku immer noch genau eine Lösung hat, ansonsten wird die Zahl wieder zurückgesetzt
                if (getSolutionAmount(sudoku) != 1)
                {
                    sudoku[row][col] = temp;
                    i--;
                }
            }
            else
            {
                i--;
            }

            // Abbruchbedingung, um eine Endlosschleife zu vermeiden; von Vorne beginnen
            attemptsTried++;

            if (attemptsTried > 500)
            {
                return createSudoku(difficulty);
                break;
            }
        }
    }
    else
    {
        // Wenn das Sudoku nicht valide ist, dann wird der Speicherplatz wieder freigegeben und ein neues Sudoku erstellt
        for (int i = 0; i < 9; i++)
        {
            free(sudoku[i]);
        }
        free(sudoku);

        return createSudoku(difficulty);
    }
    return sudoku;
}

// Gibt die Anzahl der Lösungen zurück, die das Sudoku hat
int getSolutionAmount(int **sudoku)
{
    return DonaldKnuth(sudoku, 0);
}