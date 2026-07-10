#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

static void freeArrays(int **zeilen, int **spalten, int **bloecke)
{
    for (int k = 0; k < 9; k++)
    {
        free(zeilen[k]);
        free(spalten[k]);
        free(bloecke[k]);
    }
    free(zeilen);
    free(spalten);
    free(bloecke);
}

int validate(int **matrix)
{ // 1 ist invalide, 0 ist valide; wenn er einen Fehler findet, bricht er ab
    // Diese Funktion soll prüfen, ob die übergeben Matrix valide ist.

    // Sind die Zeilen valide?
    // Matrizen; durch calloc mit 0 gefüllt
    int **zeilen = calloc(9, sizeof(int *));
    int **spalten = calloc(9, sizeof(int *));
    int **bloecke = calloc(9, sizeof(int *)); // Jede Zeile ist ein Block. wir gehen spaltenweise alle 9 Blöcke durch.

    for (int i = 0; i < 9; i++)
    {
        bloecke[i] = calloc(9, sizeof(int));
        spalten[i] = calloc(9, sizeof(int));
        zeilen[i] = calloc(9, sizeof(int)); // Speicherplatz für Spalten in den jeweiligen Zeilen reservieren
    }

    int zeilenWert = 0;
    int spaltenWert = 0;
    int blockWert = 0;

    int start_Z = 0;
    int start_S = 0;
    int echteZeile = 0;
    int echteSpalte = 0;

    // Diese Arrays sind nötig, dass wir blockWert einlesen können (wo in der Matrix sind wir?)
    const int BLOCKZEILE[9] = {0, 0, 0, 3, 3, 3, 6, 6, 6};
    const int BLOCKSPALTE[9] = {0, 3, 6, 0, 3, 6, 0, 3, 6};

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            zeilenWert = matrix[i][j];
            if (zeilenWert != 0)
            { // Nullen werden übersprungen; können doppelt vorkommen
                // Erst Zeile prüfen
                if (zeilen[i][zeilenWert - 1] == 1)
                { // Wenn die Zahl schon vorhanden ist (also in der Matrix 1 eingetragen ist)
                    fprintf(stderr, "In Zeile %d ist eine doppelte Zahl vorhanden.\n", i + 1);
                    freeArrays(zeilen, spalten, bloecke);
                    return 1;
                }
                else
                { // Sonst 1 eintragen -> Zahl ist in Zeile schon vorhanden
                    zeilen[i][zeilenWert - 1] = 1;
                }
            }

            // Dann Spalte prüfen
            spaltenWert = matrix[j][i];
            if (spaltenWert != 0)
            {
                if (spalten[spaltenWert - 1][i] == 1)
                {
                    fprintf(stderr, "In Spalte %d ist eine doppelte Zahl vorhanden.\n", i + 1);
                    freeArrays(zeilen, spalten, bloecke);
                    return 1;
                }
                else
                {
                    spalten[spaltenWert - 1][i] = 1;
                }
            }
            // 3-er Blöcke prüfen. Pro inneren Schleifendurchlauf prüfen wir ein Quadrat, welches einer Zeile in bloecke entspricht.
            // Switch case ermittelt blockWert

            start_Z = BLOCKZEILE[i];
            start_S = BLOCKSPALTE[i];

            echteZeile = start_Z + (j / 3);
            echteSpalte = start_S + (j % 3);

            blockWert = matrix[echteZeile][echteSpalte];

            if (blockWert != 0)
            {
                if (bloecke[i][blockWert - 1] == 1)
                {
                    fprintf(stderr, "In Block %d ist eine doppelte Zahl vorhanden.\n", i + 1);
                    freeArrays(zeilen, spalten, bloecke);
                    return 1;
                }
                else
                {
                    bloecke[i][blockWert - 1] = 1;
                }
            }
        }
    }
    freeArrays(zeilen, spalten, bloecke);
    return 0;
}
