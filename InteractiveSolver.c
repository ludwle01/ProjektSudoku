#include <stdio.h>
#include <stdlib.h>

// Funktionen aus anderen Projektdateien 
int DonaldKnuth(int **sudoku, int doASolve);
void returnToMenu(void);
void printMatrix(int **matrix);
void printRow(int *row);
void printBox(int **matrix, int box);
int getUserIntInput(int min, int max);
int solve(int row, int column, int **sudoku);
void output(int **matrix);

/*
Ueberprueft, ob die Eingabe des Users den Sudoku-Regeln entspricht
Rueckgabewerte:0 = Zug ist erlaubt, 1 = Zug ist nicht erlaubt
 */
int isLegalMove(int **sudoku, int row, int col,int num) {
    //Das gewaehlte Feld muss leer sein
    if(sudoku[row][col] != 0) {
        return 1;
    }

    //Zeile und Spalte ueberpruefen.
    for(int i = 0; i < 9; i++) {
        if(sudoku[row][i] == num) {
            return 1;
        }
        if(sudoku[i][col] == num) {
            return 1;
        }
    }

    //Zugehoerigen 3x3-Block ueberpruefen
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(sudoku[startRow + i][startCol + j] == num) {
                return 1;
            }
        }
    }

    return 0;
}

/*
Ueberprueft, ob das Sudoku nach dem Zug
noch mindestens eine Loesung hat
Rueckgabewerte: 0 = Sudoku bleibt loesbar, 1 = Sudoku ist danach nicht mehr loesbar
 */
int isStillSolvable(int **sudoku, int row, int col, int num) {
    sudoku[row][col] = num;

    int solutionCount = DonaldKnuth(sudoku, 0);

    sudoku[row][col] = 0;
    if(solutionCount > 0) {
        return 0;
    }
    return 1;
}

//Rueckgabewerte:0 = Sudoku ist vollstaendig ausgefuellt, 1 = Sudoku enthaelt noch mindestens ein leeres Feld
int isSudokuFinished(int **sudoku) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j] == 0) {
                return 1;
            }
        }
    }

    return 0;
}

void cancelPlay(void) {
    returnToMenu();
}

void sudokuSolved(int **sudoku) {
    printf("\nPrima, du hast das Sudoku geloest!\n");
    printf("\nMoechtest du deine Loesung in einer Datei speichern?\n");
    printf("1: Ja, als Loesung speichern\n");
    printf("2: Nein, zurueck zum Menue\n");
    printf("Deine Wahl: ");

    int saveOption = getUserIntInput(1, 2);
    if(saveOption == 1) {
        output(sudoku);

        printf("\nDas Sudoku wurde erfolgreich gespeichert!\n");
    }

    printf("\nDruecke ENTER, um fortzufahren...");
    getUserIntInput(0, 0);
    cancelPlay();
}

/*
Rueckgabewerte:
-1 = Eingabefehler
 0 = Benutzer moechte abbrechen
 1 = Gueltige Eingabe
 */
int getUserInput(int *row, int *column, int *number) {
    printf("\nDein Zug: ");

    int matches = scanf("%d %d %d", row, column, number);
    int character;

    while((character = getchar()) != '\n' && character != EOF) {
        //Eingabepuffer bis zum Zeilenende leeren.
    }

    if(matches != 3) {
        printf("FEHLER! Bitte drei ganze Zahlen eingeben, zum Beispiel: 1 2 4\n");
        return -1;
    }


    if(*row == 0 && *column == 0 && *number == 0) {
        return 0;
    }

    if( *row < 1 || *row > 9 || *column < 1 || *column > 9 || *number < 1 || *number > 9) {
        printf("FEHLER! Zeile, Spalte und Zahl muessen zwischen 1 und 9 liegen!\n");
        return -1;
    }
    return 1;
}

/*
Erstellt eine unabhaengige Kopie des aktuellen Sudokus
Die Kopie wird fuer einen Hinweis geloest, damit deraktuelle Spielstand des Benutzers unveraendert bleibt
 */

static int **createSudokuCopy(int **source) {
    if(source == NULL) {
        return NULL;
    }

    int **copy = malloc(9 * sizeof(int *));

    if(copy == NULL) {
        return NULL;
    }

    for(int i = 0; i < 9; i++) {
        copy[i] = malloc(9 * sizeof(int));

        if(copy[i] == NULL) {

            //Bereits reservierte Zeilen freigeben
            for(int j = 0; j < i; j++) {
                free(copy[j]);
            }
            free(copy);
            return NULL;
        }

        for(int j = 0; j < 9; j++) {
            copy[i][j] = source[i][j];
        }
    }
    return copy;
}


//Gibt den Speicher einer Sudoku-Kopie wieder frei
static void freeSudokuCopy(int **matrix) {
    if(matrix == NULL) {
        return;
    }

    for(int i = 0; i < 9; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

// Zeigt einen Hinweis fuer eine Zeile, einen 3x3-Block oder ein einzelnes Feld an
static void showHint(int **sudoku) {
    //Kopie anlegen, damit das Original nicht geloest wird.
    int **solution = createSudokuCopy(sudoku);

    if(solution == NULL) {
        printf("\nFehler: Fuer den Hinweis konnte kein Speicher reserviert werden.\n");
        return;
    }

    //Ausschliesslich die Kopie wird geloest
    if(solve(0, 0, solution) == 0) {
        printf("\nFuer dieses Sudoku konnte keine Loesung gefunden werden.\n");
        freeSudokuCopy(solution);
        return;
    }

    printf("\nWelche Art von Hinweis moechtest du?\n");
    printf("1: Eine bestimmte Zeile anzeigen\n");
    printf("2: Einen bestimmten 3x3-Block anzeigen\n");
    printf("3: Den Wert eines einzelnen Feldes anzeigen\n");
    printf("Deine Wahl: ");

    int hintOption = getUserIntInput(1, 3);

    //Eine vollstaendige Zeile als Hinweis anzeigen
    if(hintOption == 1) {
        printf("Welche Zeile soll angezeigt werden? (1-9): ");

        int row = getUserIntInput(1, 9);

        printf("\nEine moegliche Loesung fuer Zeile %d:\n", row);

        printRow(solution[row - 1]);

    //Einen vollstaendigen 3x3-Block anzeigen
    } else if(hintOption == 2) {
        printf("Welcher Block soll angezeigt werden?\n");
        printf("1 = oben links, 2 = oben Mitte, ..., 9 = unten rechts: ");
        int box = getUserIntInput(1, 9);

        printf("\nEine moegliche Loesung fuer Block %d:\n", box);
        printBox(solution, box);

    //Den Wert eines einzelnen Feldes anzeigen
    } else {
        printf("In welcher Zeile liegt das Feld? (1-9): ");

        int row = getUserIntInput(1, 9);

        printf("In welcher Spalte liegt das Feld? (1-9): ");

        int column = getUserIntInput(1, 9);

        printf("\nIn einer moeglichen Loesung steht im Feld [%d][%d] die Zahl %d.\n", row, column, solution[row - 1][column - 1]);
    }

    //Kopie nach der Ausgabe wieder freigeben
    freeSudokuCopy(solution);

    printf("\nDruecke ENTER, um weiterzuspielen.");

    getUserIntInput(0, 0);
}

/*
 Der Benutzer kann vor jedem neuen Spielzug entscheiden,
 ob er eine Zahl eintragen, einen Hinweis anzeigen oder
 das interaktive Loesen abbrechen will.
 */
void playSudokuInteractive(int **sudoku) {
    int row;
    int column;
    int number;
    int running = 1;

    if(isSudokuFinished(sudoku) == 0) {
        printMatrix(sudoku);
        sudokuSolved(sudoku);
        return;
    }

    printf("\nViel Erfolg beim Loesen des Sudokus!");

    printf("\nEingabe-Format: Zeile Spalte Zahl\n");

    printf("Beispiel: 1 2 4 ");

    printf("(Setzt in Zeile 1, Spalte 2, die Zahl 4 ein)\n");

    while(running) {
        printMatrix(sudoku);

        //Diese Auswahl erscheint vor jedem neuen Spielzug
        printf("\nWas moechtest du als Naechstes tun?\n");

        printf("0: Spiel abbrechen\n");
        printf("1: Eine Zahl eintragen\n");
        printf("2: Einen Hinweis anzeigen\n");
        printf("Deine Wahl: ");

        int playOption = getUserIntInput(0, 2);

        //Interaktives Spiel abbrechen
        if(playOption == 0) {
            printf("\nSpiel wurde abgebrochen.\n");
            running = 0;
            cancelPlay();
            continue;
        }

        //Einen Hinweis anzeigen
        //Danach wird die Schleife erneut gestartet und das Aktionsmenue wieder angezeigt
        if(playOption == 2) {
            showHint(sudoku);
            continue;
        }

        //Bei Option 1 Zeile, Spalte und Zahl einlesen
        int inputStatus = getUserInput(&row, &column, &number);

        if(inputStatus == 0) {
            printf("\nSpiel wurde abgebrochen.\n");
            running = 0;
            cancelPlay();

        } else if(inputStatus == -1) {
            //Bei falscher Eingabe wird erneut das Aktionsmenue angezeigt
            continue;

        } else {
            //Benutzereingaben liegen zwischen 1 und 9. Array-Indizes liegen zwischen 0 und 8
            int rowIndex = row - 1;
            int columnIndex = column - 1;

            if(isLegalMove(sudoku, rowIndex, columnIndex, number) == 1) {
                printf("FEHLER! Der Zug ist nach den Sudoku-Regeln nicht erlaubt!\n");
            } else if(isStillSolvable(sudoku, rowIndex, columnIndex, number) == 1) {
                printf("SACKGASSE! Das Sudoku ist danach nicht mehr loesbar!\n");
            } else {
                sudoku[rowIndex][columnIndex] = number;
                printf("\nERFOLG! Die %d wurde eingetragen.\n", number);
                if(isSudokuFinished(sudoku) == 0) {
                    printMatrix(sudoku);
                    running = 0;
                    sudokuSolved(sudoku);
                }
            }
        }
    }
}