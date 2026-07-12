#include "sudoku.h"

int charToValue(char c) // um auch Hex Zahlen darzustellen
{
    if (c == '.'){// leeres Feld darstellen
        return EMPTY;
    }
    if (c >= '0' && c <= '9'){ // Ziffern darstellen
        return c - '0';
    }
    if (c >= 'A' && c <= 'F'){ // zusätzliche Ziffern Hex darstellen
        return c - 'A' + 10;
    }

    if (c >= 'a' && c <= 'f'){
        return c - 'a' + 10;
    }

    return -2;      // ungültiges Zeichen
}

int **read()
{
    int **matrix = malloc(SIZE * sizeof(int *)); // Speicher reservieren

    for (int i = 0; i < SIZE; i++) // Zeilen erstellen
        matrix[i] = malloc(SIZE * sizeof(int)); // Zeile ist SIZE lang

    FILE *datei = fopen("inputSudoku.txt", "r"); // Datei mit Rätsel öffnen

    if (datei == NULL) // Fehler beim Einlesen
    {
        perror("inputSudoku.txt");

        for (int i = 0; i < SIZE; i++){
            free(matrix[i]);
        }
        free(matrix);
        return NULL;
    }

    int row = 0;
    int col = 0;
    int c;

    while ((c = fgetc(datei)) != EOF)
    {
        if (c == '\n')
        {
            if (col == 0)
                continue;

            if (col != SIZE)
            {
                fprintf(stderr,
                        "Line %d contains %d instead of %d entries.\n",
                        row + 1, col, SIZE);

                fclose(datei);
                return NULL;
            }

            row++;
            col = 0;

            if (row > SIZE)
            {
                fprintf(stderr, "Too many rows.\n");
                fclose(datei);
                return NULL;
            }

            continue;
        }

        if (c == ' ' || c == '|' || c == '-')
            continue;

        int value = charToValue(c);

        if (value == -2)
        {
            fprintf(stderr,
                    "Invalid character '%c'.\n",
                    c);

            fclose(datei);
            return NULL;
        }

        matrix[row][col] = value;
        col++;
    }

    fclose(datei);

    printf("Rätsel erfolgreich eingelesen:\n"); // eingelesenes Sudoku ausgeben
    printMatrix(matrix);

    return matrix;
}
