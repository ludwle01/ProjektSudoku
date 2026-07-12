#include <stdio.h>
#include <stdlib.h>

int **sudoku = NULL;

//Funktionen aus anderen Projektdateien
int **createSudoku(int difficulty);
void printMatrix(int **matrix);
int **read(void);
int DonaldKnuth(int **sudoku, int doASolve);
void playSudokuInteractive(int **sudoku);
void motivateMe(void);
int validate(int **matrix);
int solve(int row, int column, int **sudoku);
void output(int **matrix);
int isSudokuFinished(int **sudoku);
void sudokuSolved(int **sudoku);

//Funktionen dieser Datei
void callStartMenu(void);
void sudokuMenu(void);
void returnToMenu(void);
int getUserIntInput(int min, int max);
void checkSolvability(void);
void returnToSudokuMenu(void);

void callStartMenu(void) {
    while(1) {
        printf("Hallo User!\nIch bin Mister Masterbrain, dein persoenlicher Assistent, um Sudokus zu loesen.\n");
        printf("Wie kann ich dir heute helfen?\n");
        printf("1: Sudoku erstellen\n");
        printf("2: Sudoku einlesen\n");
        printf("Deine Wahl: ");

        int startOption = getUserIntInput(1, 2);
        if(startOption == 1) {
            printf("\nWelche Schwierigkeitsstufe soll das Sudoku haben?\n");
            printf("1: Einfach\n");
            printf("2: Mittel\n");
            printf("3: Schwer\n");
            printf("Deine Wahl: ");

            int difficulty = getUserIntInput(1, 3);
            if(difficulty == 1) {
                printf("\nEin einfaches Sudoku wird erstellt...\n\n");
            } else if(difficulty == 2) {
                printf("\nEin mittelschweres Sudoku wird erstellt...\n\n");
            } else {
                printf("\nEin schwieriges Sudoku wird erstellt...\n\n");
            }

            sudoku = createSudoku(difficulty);
            if(sudoku == NULL) {
                printf("\nDas Sudoku konnte nicht erstellt werden.\n");
                printf("Druecke ENTER, um zum Startmenue zurueckzukehren.");
                getUserIntInput(0, 0);
                continue;
            }
            printMatrix(sudoku);
            sudokuMenu();
        } else {
            printf("\nBitte beachte, dass die Datei inputSudoku.txt heisst ");
            printf("und im gleichen Ordner liegt.\n");
            printf("Hast du dies sichergestellt, druecke ENTER!");
            getUserIntInput(0, 0);
            printf("\n");

            sudoku = read();
            if(sudoku == NULL) {
                printf("\nDas Sudoku konnte nicht aus der Datei: inputSudoku.txt gelesen werden.\n");
                printf("Druecke ENTER, um zum Startmenue zurueckzukehren.");
                getUserIntInput(0, 0);
                continue;
            }

            int validationResult = validate(sudoku);
            if(validationResult == 0) {
                if(isSudokuFinished(sudoku) == 0) {
                    printf("\nDas eingelesene Sudoku ist bereits vollstaendig geloest.\n\n");
                    returnToMenu();
                    continue;
                }
                checkSolvability();
                sudokuMenu();
            } else {
                printf("\nDies ist kein gueltiges Sudoku!\n");
                printf("\nBitte ueberpruefe deine Eingabe und versuche es erneut!\n");
                returnToMenu();
                printf("Druecke ENTER, um zum Startmenue zurueckzukehren.");
                getUserIntInput(0, 0);
            }
        }
    }
}

void sudokuMenu(void) {
    while(sudoku != NULL) {
        printf("\nWas moechtest du mit dem Sudoku machen?\n");
        printf("0: Zurueck zum Menue\n");
        printf("1: Sudoku selber loesen\n");
        printf("2: Sudoku mit dem Brute-Force Algorithmus loesen\n");
        printf("3: Sudoku mit dem Donald-Knuth Algorithmus loesen\n");
        printf("4: Motivationsspruch anzeigen\n");
        printf("Deine Wahl: ");

        int menuOption = getUserIntInput(0, 4);
        if(menuOption == 0) {
            returnToMenu();
            return;
        } else if(menuOption == 1) {
            printf("\n");
            playSudokuInteractive(sudoku);
        } else if(menuOption == 2) {
            printf("Mister Masterbrain loest das Sudoku mit dem Brute-Force Algorithmus...\n");
            int solveResult = solve(0, 0, sudoku);
            if(solveResult == 1) {
                printMatrix(sudoku);
                printf("\nSoll das Sudoku gespeichert werden?\n");
                printf("1: Ja\n");
                printf("2: Nein\n");
                printf("Deine Wahl: ");

                int saveOption = getUserIntInput(1, 2);
                if(saveOption == 1) {
                    output(sudoku);
                    printf("\nDas Sudoku wurde erfolgreich gespeichert!\n");
                }
            } else {
                printf("\nMister Masterbrain hat versagt und konnte das Sudoku nicht loesen!\n");
            }

            printf("\nDruecke ENTER, um zum Startmenue zurueckzukehren.");
            getUserIntInput(0, 0);
            returnToMenu();
            return;
        } else if(menuOption == 3) {
            printf("\nMister Masterbrain loest das Sudoku mit dem Donald-Knuth Algorithmus...\n");
            int solveResult = DonaldKnuth(sudoku, 1);
            if(solveResult == 0) {
                printMatrix(sudoku);
                printf("\nSoll das Sudoku gespeichert werden?\n");
                printf("1: Ja\n");
                printf("2: Nein\n");
                printf("Deine Wahl: ");

                int saveOption = getUserIntInput(1, 2);
                if(saveOption == 1) {
                    output(sudoku);
                    printf("\nDas Sudoku wurde erfolgreich gespeichert!\n");
                }
            } else {
                printf("\nMister Masterbrain hat versagt und konnte das Sudoku nicht loesen!\n");
            }
            printf("\nDruecke ENTER, um zum Startmenue zurueckzukehren.");
            getUserIntInput(0, 0);
            returnToMenu();
            return;
        } else {
            printf("\n");
            motivateMe();
            returnToSudokuMenu();
        }
    }
}

void checkSolvability(void) {
    int solutionCount = DonaldKnuth(sudoku, 0);
    if(solutionCount <= 0) {
        printf("\nMister Masterbrain sagt: dieses Sudoku ist unloesbar\n");
    } else if(solutionCount == 1) {
        printf("\nDas Sudoku ist loesbar und besitzt genau eine Loesung.\n");
    } else if(solutionCount >= 101) {
        printf("\nDas Sudoku ist loesbar und besitzt mindestens 101 Loesungen.\n");
    } else {
        printf("\nDas Sudoku ist loesbar und besitzt %d Loesungen.\n", solutionCount);
    }
    returnToSudokuMenu();
}

void returnToSudokuMenu(void) {
    printf("\nDruecke ENTER, um zum Sudoku-Menue zurueckzukehren.");
    getUserIntInput(0, 0);
}

void returnToMenu(void) {
    if(sudoku == NULL) {
        return;
    }
    for(int i = 0; i < 9; i++) {
        free(sudoku[i]);
    }
    free(sudoku);
    sudoku = NULL;
}

int getUserIntInput(int min, int max) {
    //Bei min == 0 und max == 0 wird nur auf ENTER gewartet.
    if(min == 0 && max == 0) {
        int character;
        while((character = getchar()) != '\n' && character != EOF) {
            //Eingabepuffer bis zum Zeilenende leeren.
        }
        return 0;
    }

    while(1) {
        int option;
        int inputResult = scanf("%d", &option);
        int character;
        while((character = getchar()) != '\n' && character != EOF) {
            //Eingabepuffer bis zum Zeilenende leeren.
        }

        if(inputResult == 1 && option >= min && option <= max) {
            return option;
        }
        if(inputResult == EOF) {
            exit(EXIT_SUCCESS);
        }
        printf("Diese Eingabe versteht Mister Masterbrain nicht. Bitte waehle eine Zahl zwischen ");
        printf("%d und %d: ", min, max);
    }
}

int main(void) {
    callStartMenu();

    return 0;
}