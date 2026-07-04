#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

int **read()
{
    int **matrix = malloc(9 * sizeof(int *)); // Pointer der auf Pointer zeigt (Zeilen)
    for (int i = 0; i < 9; i++)
    {
        matrix[i] = malloc(9 * sizeof(int)); // Speicherplatz für Spalten in den jeweiligen Zeilen reservieren
    }
    FILE *datei = fopen("inputSudoku.txt", "r"); // Datei öffnen
    if (datei == NULL)
    { // Wenn Datei nicht existiert, Fehler
        perror("Fehler beim Oeffnen");
        for (int i = 0; i < 9; i++)
        {
            free(matrix[i]);
        }
        free(matrix);
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
        { // Wenn Eintrag nicht zwischen 0 und 9 -> Error
            perror("Ein Eintrag in  inputSudoku.txt ist nicht zwischen 0 und 9.");
            fclose(datei);
            return NULL;
        }
        if (zeile > 9)
        {
            perror("Du hast du viele Zeilen!");
            return NULL;
        }
        if (zeile < 9)
        {
            matrix[zeile][eintrag] = n - '0';
            eintrag++;
        }
    }
    printf("Das eingegebene Sudoku:\n");
    printMatrix(matrix);
    fclose(datei);
    return matrix;
}
