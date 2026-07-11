#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

void freeMatrix(int **matrix)
{
    if (matrix == NULL)
        return;

    for (int i = 0; i < 9; i++)
    {
        free(matrix[i]); // Erst die einzelnen Zeilen freigeben
    }
    free(matrix); // Dann das Array von Zeilen-Pointern freigeben
}

int **read()
{
    // NOTIZ: FREE() AM ENDE NICHT VERGESSEN
    int **matrix = malloc(9 * sizeof(int *)); // Pointer der auf Pointer zeigt (Zeilen)
    for (int i = 0; i < 9; i++)
    {
        matrix[i] = malloc(9 * sizeof(int)); // Speicherplatz für Spalten in den jeweiligen Zeilen reservieren
    }
    FILE *datei = fopen("inputSudoku.txt", "r"); // Datei öffnen
    if (datei == NULL)
    { // Wenn Datei nicht existiert, Fehler
        perror("Fehler beim Oeffnen");
        freeMatrix(matrix);
        return NULL;
    }
    int zeile = 0;
    int eintrag = 0;
    int n = 0;
    while ((n = fgetc(datei)) != EOF)
    {

        if (n == '\n')
        { // Wenn wir am Ende der Zeile sind
            if (eintrag != 9 && eintrag != 0)
            { // Wenn != 9 Einträge
                fprintf(stderr, "Deine Matrix hat in Zeile %d keine 9 Eintraege!\n", zeile);
                fclose(datei);
                freeMatrix(matrix);
                return NULL;
            }
            if (eintrag == 0 && n == '\n')
            {
                continue;
            } // Leere Zeilen werden übersprungen
            eintrag = 0;
            zeile++;
            continue;
        }

        if (n == ' ' || n == '|' || n == '-')
        { // Leerzeichen ignorieren
            continue;
        }
        if (n < '0' || n > '9')
        { // Wenn Eintrag nicht zwischen 0 und 9 Error
            perror("Der Eintrag ist nicht zwischen 0 und 9.");
            fclose(datei);
            freeMatrix(matrix);
            return NULL;
        }
        // PROBLEMATISCH
        if (zeile >= 9)
        {
            perror("Du hast zu viele Zeilen!");
            freeMatrix(matrix);
            fclose(datei);
            return NULL;
        }

        if (eintrag >= 9)
        {
            fprintf(stderr, "Fehler: Zu viele Eintraege in Zeile %d!\n", zeile + 1);
            fclose(datei);
            freeMatrix(matrix);
            return NULL;
        }
        matrix[zeile][eintrag] = n - '0';
        eintrag++;
    }

    fclose(datei);
    // Letzte Ziele Prüfen
    if (eintrag != 0)
    {
        if (eintrag != 9)
        {
            fprintf(stderr, "Fehler: Letzte Zeile hat keine 9 Eintraege!\n");
            freeMatrix(matrix);
            return NULL;
        }
        zeile++;
    }

    // Prüfen, ob wir auch wirklich ein 9 Zeilen haben
    if (zeile != 9)
    {
        fprintf(stderr, "Fehler: Das Sudoku ist unvollstaendig (nur %d von 9 Zeilen).\n", zeile);
        freeMatrix(matrix);
        return NULL;
    }
    printf("Successfully read the following puzzle:\n");
    printMatrix(matrix);

    return matrix;
}
