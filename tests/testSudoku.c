#include <stdio.h>
#include <stdlib.h>
#include "../sudoku.h"

int testsGesamt = 0;
int testsFehlgeschlagen = 0;

int pruefeTest(char *name, int ergebnis, int erwartet) {
    testsGesamt++;

    if (ergebnis == erwartet) {
        printf("BESTANDEN: %s\n", name);
        return 0;
    } else {
        printf("NICHT BESTANDEN: %s\n", name);
        printf("Erwartet: %d, erhalten: %d\n", erwartet, ergebnis);
        return 1;
    }
}

int **erstelleTestSudoku(int werte[9][9]) {
    int **matrix = malloc(9 * sizeof(int *));

    for (int i = 0; i < 9; i++) {
        matrix[i] = malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++) {
            matrix[i][j] = werte[i][j];
        }
    }
    return matrix;
}

void loescheTestSudoku(int **matrix) {
    for (int i = 0; i < 9; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int istVollstaendig(int **matrix) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (matrix[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void testeValidate(void) {
    int gueltigeWerte[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int **matrix = erstelleTestSudoku(gueltigeWerte);
    testsFehlgeschlagen += pruefeTest("Gueltiges Sudoku wird erkannt", validate(matrix), 0);
    loescheTestSudoku(matrix);

    gueltigeWerte[0][2] = 5;
    matrix = erstelleTestSudoku(gueltigeWerte);
    testsFehlgeschlagen += pruefeTest("Doppelte Zahl in einer Zeile", validate(matrix), 1);
    loescheTestSudoku(matrix);

    gueltigeWerte[0][2] = 0;
    gueltigeWerte[2][0] = 5;
    matrix = erstelleTestSudoku(gueltigeWerte);
    testsFehlgeschlagen += pruefeTest("Doppelte Zahl in einer Spalte", validate(matrix), 1);
    loescheTestSudoku(matrix);

    int blockFehler[9][9] = {0};
    blockFehler[0][0] = 5;
    blockFehler[1][1] = 5;
    matrix = erstelleTestSudoku(blockFehler);
    testsFehlgeschlagen += pruefeTest("Doppelte Zahl in einem Block", validate(matrix), 1);
    loescheTestSudoku(matrix);
}

void testeValidateCell(void) {
    int werte[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int **matrix = erstelleTestSudoku(werte);

    testsFehlgeschlagen += pruefeTest("Erlaubte Zahl fuer ein Feld", validate_cell(0, 2, 4, matrix), 1);
    testsFehlgeschlagen += pruefeTest("Zahl bereits in der Zeile", validate_cell(0, 2, 5, matrix), 0);
    testsFehlgeschlagen += pruefeTest("Zahl bereits in der Spalte", validate_cell(0, 2, 8, matrix), 0);
    testsFehlgeschlagen += pruefeTest("Zahl bereits im Block", validate_cell(0, 2, 6, matrix), 0);

    loescheTestSudoku(matrix);
}

void testeSolver(void) {
    int werte[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int **matrix = erstelleTestSudoku(werte);

    testsFehlgeschlagen += pruefeTest("Brute-Force findet eine Loesung", solve(0, 0, matrix), 1);
    testsFehlgeschlagen += pruefeTest("Brute-Force-Loesung ist vollstaendig", istVollstaendig(matrix), 0);
    testsFehlgeschlagen += pruefeTest("Brute-Force-Loesung ist gueltig", validate(matrix), 0);

    loescheTestSudoku(matrix);
}

void testeDonaldKnuth(void) {
    int werte[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int **matrix = erstelleTestSudoku(werte);

    testsFehlgeschlagen += pruefeTest("Donald-Knuth findet eine Loesung", DonaldKnuth(matrix, 1), 0);
    testsFehlgeschlagen += pruefeTest("Donald-Knuth-Loesung ist vollstaendig", istVollstaendig(matrix), 0);
    testsFehlgeschlagen += pruefeTest("Donald-Knuth-Loesung ist gueltig", validate(matrix), 0);

    loescheTestSudoku(matrix);

    matrix = erstelleTestSudoku(werte);
    testsFehlgeschlagen += pruefeTest("Sudoku besitzt genau eine Loesung", DonaldKnuth(matrix, 0), 1);
    loescheTestSudoku(matrix);
}

int pruefeErstelltesSudoku(void) {
    int **matrix = createSudoku(1);
    if (matrix == NULL) {
        return 1;
    }

    int ergebnis = 0;
    if (validate(matrix) != 0) {
        ergebnis = 1;
    }
    if (DonaldKnuth(matrix, 0) != 1) {
        ergebnis = 1;
    }

    loescheTestSudoku(matrix);
    return ergebnis;
}

void testeCreate(void) {
    testsFehlgeschlagen += pruefeTest("Create erstellt ein gueltiges und eindeutig loesbares Sudoku", pruefeErstelltesSudoku(), 0);
}

int pruefeLeereDatei(void) {
    char *originalName = "inputSudoku.txt";
    char *backupName = "tests/inputSudoku_backup_test.txt";
    int originalVorhanden = 0;
    int ergebnis = 0;

    FILE *datei = fopen(originalName, "r");

    if (datei != NULL) {
        fclose(datei);
        originalVorhanden = 1;

        FILE *backup = fopen(backupName, "r");

        if (backup != NULL) {
            fclose(backup);
            return 1;
        }
        if (rename(originalName, backupName) != 0) {
            return 1;
        }
    }

    datei = fopen(originalName, "w");

    if (datei == NULL) {
        if (originalVorhanden == 1) {
            rename(backupName, originalName);
        }
        return 1;
    }

    fclose(datei);

    int **matrix = read();
    if (matrix != NULL) {
        ergebnis = 1;
        loescheTestSudoku(matrix);
    }
    if (remove(originalName) != 0) {
        ergebnis = 1;
    }
    if (originalVorhanden == 1 && rename(backupName, originalName) != 0) {
        ergebnis = 1;
    }
    return ergebnis;
}

void testeLeereDatei(void) {
    testsFehlgeschlagen += pruefeTest("Leere Eingabedatei wird abgefangen", pruefeLeereDatei(), 0);
}

int main(void) {
    printf("Sudoku-Tests werden gestartet...\n\n");

    //verhindert ausgaben von validate.c, prüft ob windows oder macos/linux
    #ifdef _WIN32
        freopen("NUL", "w", stderr);
    #else
        freopen("/dev/null", "w", stderr);
    #endif

    testeValidate();
    testeValidateCell();
    testeSolver();
    testeDonaldKnuth();
    testeCreate();
    testeLeereDatei();

    int testsBestanden = testsGesamt - testsFehlgeschlagen;
    printf("\n%d von %d Tests bestanden.\n", testsBestanden, testsGesamt);
    if (testsFehlgeschlagen == 0) {
        return 0;
    }
    return 1;
}