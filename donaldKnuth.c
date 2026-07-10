#include <stdio.h>
#include <stdlib.h>
#include "main2.h"

// Funktion wird hier deklariert, damit sie übersichtlicherweise ganz unten im Code stehen kann und der Compiler nicht meckert
int solveMatrix(int depth, int coveredColumns[], int solution[], int **matrix);
void countSolutionsMatrix(int depth, int coveredColumns[], int solution[], int **matrix, int *solutionCount);

// Wenn doASolve == 1, dann wird das Sudoku gelöst und in Textdatei gespeichert
// Rückgabe ist -1 wenn das Sudoku nicht lösbar ist, ansonsten 0
// Wenn doASolve != 1, dann wird die Anzahl an Lösungen gezählt und zurückgegeben

// Funktion, die alle möglichen Spielzüge speichert
int DonaldKnuth(int **sudoku, int doASolve)
{
    // 1. Feld-Regel (Spalten 0 - 80): jedes Feld braucht eine Zahl
    // 2. Zeilen-Regel (Spalten 81 - 161): Jede Zeile braucht jede Zahl genau 1 Mal
    // 3. Spalten-Regel (Spalten 162 - 242): Jede Spalte braucht jede Zahl genau 1 Mal
    // 4. Block-Regel (Spalten 243 - 323): Jeder Block braucht jede Zahl genau 1 Mal

    int **matrix = (int **)malloc(729 * sizeof(int *));
    for (int i = 0; i < 729; i++)
    {
        matrix[i] = (int *)calloc(324, sizeof(int));
    }

    // Zeilen-Zähler
    int matrixRow = 0;

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            // Für jedes Feld im Sudoku alle 9 Zahlen durchgehen
            for (int num = 1; num <= 9; num++)
            {

                // Wenn ein Feld belegt ist, nur die entsprechende Zahl eintragen --> Wenn im ersten Feld eine 9 steht, sind in matrix die Zeilen für die Zahlen 1-8 leer (nur Nullen)
                if (sudoku[row][col] != 0 && sudoku[row][col] != num)
                {
                    matrixRow++;
                    continue;
                }
                // Regel 1
                int indexCell = row * 9 + col;

                // Regel 2
                int indexRow = 81 + (row * 9) + (num - 1);

                // Regel 3
                int indexCol = 162 + (col * 9) + (num - 1);

                // Regel 4
                int boxIndex = 0;

                // Überprüfen in welcher 3x3 Box wir uns befinden
                if (row == 0 || row == 1 || row == 2)
                {
                    if (col == 0 || col == 1 || col == 2)
                    {
                        boxIndex = 0;
                    }
                    else if (col == 3 || col == 4 || col == 5)
                    {
                        boxIndex = 1;
                    }
                    else if (col == 6 || col == 7 || col == 8)
                    {
                        boxIndex = 2;
                    }
                }
                else if (row == 3 || row == 4 || row == 5)
                {
                    if (col == 0 || col == 1 || col == 2)
                    {
                        boxIndex = 3;
                    }
                    else if (col == 3 || col == 4 || col == 5)
                    {
                        boxIndex = 4;
                    }
                    else if (col == 6 || col == 7 || col == 8)
                    {
                        boxIndex = 5;
                    }
                }
                else if (row == 6 || row == 7 || row == 8)
                {
                    if (col == 0 || col == 1 || col == 2)
                    {
                        boxIndex = 6;
                    }
                    else if (col == 3 || col == 4 || col == 5)
                    {
                        boxIndex = 7;
                    }
                    else if (col == 6 || col == 7 || col == 8)
                    {
                        boxIndex = 8;
                    }
                }

                int indexBox = 243 + (boxIndex * 9) + (num - 1);

                matrix[matrixRow][indexCell] = 1;
                matrix[matrixRow][indexRow] = 1;
                matrix[matrixRow][indexCol] = 1;
                matrix[matrixRow][indexBox] = 1;

                matrixRow++;
            }
        }
    }

    // Ziel ist es, später in diesem Array überall eine 1 zu haben, dann ist das Sudoku gelöst.
    int coveredColumns[324] = {0};

    // Hier werden die 81 fertigen Zahlen (entsprechende Zeilen aus der 729x324 Matrix)) gespeichert
    int solution[81] = {0}; // Array, um die Lösung zu speichern

    // Zähler, wie viele Zahlen schon gesetzt wurden
    int depth = 0;

    // Erst die gegebenen Zahlen eintragen
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku[row][col] != 0)
            {
                int num = sudoku[row][col];

                // Die vier Spalten-Indizes (Regeln) ermitteln
                int indexCell = row * 9 + col;
                int indexRow = 81 + (row * 9) + (num - 1);
                int indexCol = 162 + (col * 9) + (num - 1);

                int boxIndex = 0;
                // Überprüfen in welcher 3x3 Box wir uns befinden
                if (row == 0 || row == 1 || row == 2)
                {
                    if (col == 0 || col == 1 || col == 2)
                    {
                        boxIndex = 0;
                    }
                    else if (col == 3 || col == 4 || col == 5)
                    {
                        boxIndex = 1;
                    }
                    else if (col == 6 || col == 7 || col == 8)
                    {
                        boxIndex = 2;
                    }
                }
                else if (row == 3 || row == 4 || row == 5)
                {
                    if (col == 0 || col == 1 || col == 2)
                    {
                        boxIndex = 3;
                    }
                    else if (col == 3 || col == 4 || col == 5)
                    {
                        boxIndex = 4;
                    }
                    else if (col == 6 || col == 7 || col == 8)
                    {
                        boxIndex = 5;
                    }
                }
                else if (row == 6 || row == 7 || row == 8)
                {
                    if (col == 0 || col == 1 || col == 2)
                    {
                        boxIndex = 6;
                    }
                    else if (col == 3 || col == 4 || col == 5)
                    {
                        boxIndex = 7;
                    }
                    else if (col == 6 || col == 7 || col == 8)
                    {
                        boxIndex = 8;
                    }
                }

                int indexBox = 243 + (boxIndex * 9) + (num - 1);

                // Die entsprechenden 4 Regeln eintragen -> return -1 wenn eine Regel gebrochen wird
                if (coveredColumns[indexCell] == 0)
                {
                    coveredColumns[indexCell] = 1;
                }
                else
                {
                    return -1;
                }

                if (coveredColumns[indexRow] == 0)
                {
                    coveredColumns[indexRow] = 1;
                }
                else
                {
                    return -1;
                }

                if (coveredColumns[indexCol] == 0)
                {
                    coveredColumns[indexCol] = 1;
                }
                else
                {
                    return -1;
                }

                if (coveredColumns[indexBox] == 0)
                {
                    coveredColumns[indexBox] = 1;
                }
                else
                {
                    return -1;
                }

                // Die Zeile in der großen Matrix
                solution[depth] = (row * 81) + (col * 9) + (num - 1);

                depth++;
            }
        }
    }

    // Wenn doASolve == 1 ist, dann soll die Lösung in Sudoku gespeichert werden
    // Wenn doASolve != 1 ist, dann soll gezählt werden, wie viele Lösungen es gibt
    if (doASolve == 1)
    {
        // Hier beginnt die Rekursion
        int result = solveMatrix(depth, coveredColumns, solution, matrix);

        if (result == 1)
        {
            // Fertige Lösung in die Matrix eintragen
            for (int i = 0; i < 81; i++)
            {
                // Rückrechnung von der Matrixzeile in Reihe, Spalte und Zahl
                int row = solution[i] / 81;
                int col = (solution[i] % 81) / 9;
                int num = (solution[i] % 9) + 1;

                sudoku[row][col] = num;
            }

            // Speicherplatz wieder freigeben
            for (int i = 0; i < 729; i++)
            {
                free(matrix[i]);
            }
            free(matrix);
            return 0;
        }
        else
        {
            // Speicherplatz wieder freigeben
            for (int i = 0; i < 729; i++)
            {
                free(matrix[i]);
            }
            free(matrix);

            return -1;
        }
    }
    else
    {
        int solutionCount = 0;

        // Wenn doASolve != 1 Lösungen zählen
        countSolutionsMatrix(depth, coveredColumns, solution, matrix, &solutionCount);

        // Speicherplatz wieder freigeben
        for (int i = 0; i < 729; i++)
        {
            free(matrix[i]);
        }
        free(matrix);

        return solutionCount;
    }
}

// Rekursiver Aufruf, welcher das Sudoku löst
// Gibt 1 zurück, wenn das Sudoku lösbar ist, ansonsten 0
int solveMatrix(int depth, int coveredColumns[], int solution[], int **matrix)
{
    // Zuerst finden wir heraus, welcher Indize in coveredColumns die nächste 0 hat
    int targetColumn = -1;
    for (int i = 0; i < 324; i++)
    {
        if (coveredColumns[i] == 0)
        {
            targetColumn = i;
            break;
        }
    }

    // Wenn es keine 0 mehr in coveredColumns gibt, ist das Sudoku gelöst --> Basisfall
    if (targetColumn == -1)
    {
        return 1;
    }

    // Gehe jede zeile durch und prüfe ob sie die nächste Null abdeckt
    for (int i = 0; i < 729; i++)
    {
        if (matrix[i][targetColumn] == 1)
        {

            // Überprüfen, ob diese Zahl gegen keine anderen Regeln verstößt
            int isValid = 1;
            for (int j = 0; j < 324; j++)
            {
                if (matrix[i][j] == 1 && coveredColumns[j] == 1)
                {
                    isValid = 0;
                    break;
                }
            }

            // Wenn die Zahl gültig ist, dann in coveredColumns und solution eintragen und nächste Rekursion aufrufen
            if (isValid == 1)
            {
                for (int j = 0; j < 324; j++)
                {
                    if (matrix[i][j] != 0)
                    {
                        coveredColumns[j] = 1;
                    }
                }

                solution[depth] = i;

                // Mit den eingetragenene Werten wird das Soduko nun weiter ausgefüllt
                // Gibt es dabei eine Sackgasse, so wird die Lösung rückgängig gemacht und die nächste Zeile durchiteriert
                int isDeadEnd = solveMatrix(depth + 1, coveredColumns, solution, matrix);

                if (isDeadEnd == 1)
                {
                    return 1;
                }
                else
                {
                    // Wenn es eine Sackgasse ist, dann die Änderungen rückgängig machen
                    for (int j = 0; j < 324; j++)
                    {
                        if (matrix[i][j] != 0)
                        {
                            coveredColumns[j] = 0;
                        }
                    }
                    solution[depth] = 0;
                }
            }
        }
    }
    return 0;
}

// Gibt die Anzahl der gefundenen Lösungen zurück
void countSolutionsMatrix(int depth, int coveredColumns[], int solution[], int **matrix, int *solutionCount)
{
    // 1. Nächste 0 in coveredColumns suchen
    int targetColumn = -1;
    for (int i = 0; i < 324; i++)
    {
        if (coveredColumns[i] == 0)
        {
            targetColumn = i;
            break;
        }
    }

    if (targetColumn == -1)
    {
        (*solutionCount)++;
        return;
    }

    // Gehe jede Zeile durch
    for (int i = 0; i < 729; i++)
    {
        if (matrix[i][targetColumn] == 1)
        {
            int isValid = 1;
            for (int j = 0; j < 324; j++)
            {
                if (matrix[i][j] == 1 && coveredColumns[j] == 1)
                {
                    isValid = 0;
                    break;
                }
            }

            if (isValid == 1)
            {
                for (int j = 0; j < 324; j++)
                {
                    if (matrix[i][j] != 0)
                    {
                        coveredColumns[j] = 1;
                    }
                }
                solution[depth] = i;

                countSolutionsMatrix(depth + 1, coveredColumns, solution, matrix, solutionCount);

                if (*solutionCount >= 101)
                {
                    return;
                }

                for (int j = 0; j < 324; j++)
                {
                    if (matrix[i][j] != 0)
                    {
                        coveredColumns[j] = 0;
                    }
                }
                solution[depth] = 0;
            }
        }
    }
}
