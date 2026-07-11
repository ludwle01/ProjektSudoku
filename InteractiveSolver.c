#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DonaldKnuth(int **sudoku, int doASolve);
void returnToMenu();
void printMatrix(int **matrix);
int getUserIntInput(int min, int max);
void output(int **matrix);

// Überprüft ob die User Eingabe den Sudoku Regeln entspricht (0 = Ja, 1 = Nein)
int isLegalMove(int **sudoku, int row, int col, int num) {
    // Überprüfen ob da schon eine Zahl steht
    if (sudoku[row][col] != 0) {
        return 1;
    }

    // Überprüfen ob die Zahl in der Reihe oder Spalte schon steht
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num) {
            return 1;
        }
        if (sudoku[i][col] == num) {
            return 1;
        }
    }

    // Überprüfen ob die Zahl in dem 3x3 Feld schon steht
    int startRow = (row / 3) * 3; // int-Division schneidet die Nachkommastellen weg
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == num) {
                return 1;
            }
        }
    }
    return 0;
}

// Überprüft ob das Sudoku nach der User Eingabe noch lösbar ist oder in einer Sackgasse endet
int isStillSolvable(int **sudoku, int row, int col, int num) {
    // User-Zahl in das Sudoku eintragen
    sudoku[row][col] = num;

    // Anzahl der Lösungen ermitteln
    int solvable = DonaldKnuth(sudoku, 0);

    // User-Zahl wieder rauslöschen
    sudoku[row][col] = 0;

    // Anzahl der Lösungen zurückgeben
    if(solvable == 1){
        return 0;
    }
    return 1;
}

// Überprüft ob das Sudoku fertig ist (0 = Fertig, 1 = Nicht fertig)
int isSudokuFinished(int **sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void cancelPlay() {
    returnToMenu();
}

// Wird aufgerufen, sobald das Sudoku gelöst wurde
void sudokuSolved(int **sudoku) {
    printf("\nPrima, du hast das Sudoku geloest!\n\n");
    printf("\nMoechtest du deine Loesung in einer Datei speichern?\n");
    printf("1: Ja, als Loesung speichern\n2: Nein, zurueck zum Menue\nDeine Wahl: ");
    
    int temp = getUserIntInput(1, 2);
    
    if (temp == 1) {
        output(sudoku);

        printf("\nDas Sudoku wurde erfolgreich gespeichert!\n");
    }
    
    printf("\nDruecke ENTER um fortzufahren...");
    getUserIntInput(0, 0);
    cancelPlay();
}

// Eingabefunktion mit welcher der User Zahlen in das Sudoku eintragen kann
//-1 = Eingabefehler; 0 = Benutzer möchte abbrechen; 1 = gültiger Spielzug
int getUserInput(int *r, int *c, int *n) {
    printf("\nDein Zug: ");
    
    int matches = scanf("%d %d %d", r, c, n);

    int temp;
    while((temp = getchar()) != '\n' && temp != EOF);

    // Abfrage ob der User das Eingabeformat eingehalten hat
    if(matches != 3) {
        printf("FEHLER! Bitte drei ganze Zahlen eingeben, zum Beispiel: 1 2 4\n");
        return -1;
    }

    if(*r == 0 && *c == 0 && *n == 0) {
        return 0;
    }

    if (*r < 1 || *r > 9 || *c < 1 || *c > 9 || *n < 1 || *n > 9) {
        printf("FEHLER Zeile, Spalte und Zahl muessen zwischen 1 und 9 liegen!\n");
        return -1;
    }
    
    //Eingabe ist gültig
    return 1;
}

// Funktion welche dem User das ausfüllen eine Sudokus ermöglicht
void playSudokuInteractive(int **sudoku) {
    int row, col, num;
    int running = 1;

    printf("\n\nViel Erfolg beim loesen des Sudokus!");
    printf("\n\nEingabe-Format: Zeile Spalte Zahl\n");
    printf("Beispiel: 1 2 4 (Setzt in Zeile 1, Spalte 2, die Zahl '4' ein)\n");
    printf("Zum Beenden tippe: 0 0 0\n");

    while (running) {
        printMatrix(sudoku);

        int status = getUserInput(&row, &col, &num);

        if (status == 0) {
            printf("\nSpiel wurde abgebrochen\n");
            running = 0;
            cancelPlay();
        } else if (status == -1) {
            continue; // Eingabefehler des Users
        } else {
            // Indexverschiebung da Arrays bei 0 beginnen
            int rIndex = row - 1;
            int cIndex = col - 1;

            // Überprüfung ob der Zug den Sudoku Regeln entspricht
            if (isLegalMove(sudoku, rIndex, cIndex, num) == 1) {
                printf("FEHLER! Zug ist nach Sudoku-Regeln nicht erlaubt!\n");
            } 
            // Abfrage: Zahl darf gesetzt werden, aber ist das Sudoku danach noch lösbar
            else if (isStillSolvable(sudoku, rIndex, cIndex, num) == 1) {
                printf("SACKGASSE! Das Sudoku ist danach nicht mehr loesbar!\n");
            } 
            // Es handelt sich um einen gültigen Zug
            else {
                sudoku[rIndex][cIndex] = num;
                printf("\nERFOLG! Die %d wurde eingetragen.\n", num);
                
                // Prüfen ob das Sudoku fertig ist
                if (isSudokuFinished(sudoku) == 0) {
                    printMatrix(sudoku);
                    running = 0;
                    sudokuSolved(sudoku);
                }
            }
        }
    }
}