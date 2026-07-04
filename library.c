#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

int** read(){
    //NOTIZ: FREE() AM ENDE NICHT VERGESSEN
    int **matrix = malloc(9 * sizeof(int*));    //Pointer der auf Pointer zeigt (Zeilen)
    for (int i = 0; i < 9; i++) {
        matrix[i] = malloc(9 * sizeof(int));    //Speicherplatz für Spalten in den jeweiligen Zeilen reservieren
    }
    FILE *datei = fopen("sudoku.txt", "r");   //Datei öffnen
    if (datei == NULL) {                        //Wenn Datei nicht existiert, Fehler
        perror("Fehler beim Oeffnen");
        for (int i = 0; i < 9; i++){
            free(matrix[i]);
        } 
        free(matrix);
        return NULL;
    }
    int zeile = 0;
    int eintrag = 0;
    int n = 0;
    while((n = fgetc(datei)) != EOF){
        
        if(n == '\n'){  //Wenn wir am Ende der Zeile sind
            if(eintrag != 9 && eintrag != 0){       //Wenn != 9 Einträge
                fprintf(stderr, "Deine Matrix hat in Zeile %d keine 9 Eintraege!\n", zeile);
                fclose(datei);
                return NULL;
            }
            if(eintrag == 0 && n == '\n' ) {continue;}  //Leere Zeilen werden übersprungen
            eintrag = 0;
            zeile ++;
            continue;
        }

        if( n == ' ' || n == '|' || n == '-'){              //Leerzeichen ignorieren
            continue;
        }
        if(n<'0' || n > '9'){     //Wenn Eintrag nicht zwischen 0 und 9 Error
            perror("Der Eintrag ist nicht zwischen 0 und 9.");
            fclose(datei);
            return NULL;
        }
        //PROBLEMATISCH
        if(zeile > 9){
            perror("Du hast zu viele Zeilen!");
            return NULL;
        }
        if (zeile < 9) {
            matrix[zeile][eintrag] = n - '0';
            eintrag++;
        }
   
    }
    printf("Das eingegebene Sudoku:\n");
    printMatrix(matrix);
    fclose(datei);
    return matrix; 
}




int validate(int** matrix){         //1 ist invalide, 0 ist valide; wenn er einen Fehler findet, bricht er ab
    //Diese Funktion soll prüfen, ob die übergeben Matrix valide ist. 
    
    //Sind die Zeilen valide?
    //Matrizen; durch calloc mit 0 gefüllt
    int **zeilen = calloc(9, sizeof(int*));
    int **spalten = calloc(9, sizeof(int*));
    int **bloecke = calloc(9, sizeof(int*));    //Jede Zeile ist ein Block. wir gehen spaltenweise alle 9 Blöcke durch.

    for (int i = 0; i < 9; i++) {
        bloecke[i] = calloc(9, sizeof(int));
        spalten[i] = calloc(9, sizeof(int));
        zeilen[i] = calloc(9, sizeof(int));    //Speicherplatz für Spalten in den jeweiligen Zeilen reservieren
    }

    int zeilenWert=0;
    int spaltenWert=0;
    int blockWert=0;

    int start_Z = 0;
    int start_S = 0;
    int echteZeile = 0;
    int echteSpalte = 0;

    //Diese Arrays sind nötig, dass wir blockWert einlesen können (wo in der Matrix sind wir?)
    const int BLOCKZEILE[9] = {0, 0, 0, 3, 3, 3, 6, 6, 6};
    const int BLOCKSPALTE[9] = {0, 3, 6, 0, 3, 6, 0, 3, 6};

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            zeilenWert = matrix[i][j];
            if(zeilenWert != 0){   //Nullen werden übersprungen; können doppelt vorkommen
                //Erst Zeile prüfen
                if(zeilen[i][zeilenWert-1] == 1){    //Wenn die Zahl schon vorhanden ist (also in der Matrix 1 eingetragen ist) 
                    fprintf(stderr, "In Zeile %d ist eine doppelte Zahl vorhanden.\n", i+1);
                    return 1;
                }else{      //Sonst 1 eintragen -> Zahl ist in Zeile schon vorhanden
                    zeilen[i][zeilenWert-1] = 1;
                }
            }

            //Dann Spalte prüfen
            spaltenWert = matrix[j][i];
            if(spaltenWert != 0){
                if(spalten[spaltenWert-1][i] == 1){
                    fprintf(stderr, "In Spalte %d ist eine doppelte Zahl vorhanden.\n", i+1);
                    return 1;
                }else{
                    spalten[spaltenWert-1][i] = 1;
                }
            }
            //3-er Blöcke prüfen. Pro inneren Schleifendurchlauf prüfen wir ein Quadrat, welches einer Zeile in bloecke entspricht.
            //Switch case ermittelt blockWert

            start_Z = BLOCKZEILE[i];
            start_S = BLOCKSPALTE[i];

            echteZeile  = start_Z + (j / 3);
            echteSpalte = start_S + (j % 3);

            blockWert = matrix[echteZeile][echteSpalte];

            if(blockWert != 0){
                if(bloecke[i][blockWert-1] == 1){
                    fprintf(stderr, "In Block %d ist eine doppelte Zahl vorhanden.\n", i+1);
                    return 1;
                }else{
                    bloecke[i][blockWert-1] = 1;
                }
            }


        }
        

    }
   
    //Wenn die for-Schleife durchgelaufen ist passen die Zeilen und spalten hoffentlich
    /*  auskommentieren, wenn man spalten und zeilen matrizen sehen will :)
    printf("\n");
    printf("Zeilen:\n");
    printMatrix(zeilen);
     printf("\n");
    printf("Spalten:\n");
    printMatrix(spalten);
    */
    return 0;

}



void output(int** matrix){
    FILE *datei = fopen("outputSudoku.txt", "w");
    //Counter, dass das Programm weiß, wann es Trennstriche augeben muss
    int counter = 0;
    int verschiebung = 0;   //Zeilen counter geht auch bei "----" hoch -> i geht auch hoch -> matrix[i] wird problematisch
    //Verschachtelte for Schleife
    for(int i=0; i<11; i++){
        if(counter == 3 || counter == 7){
            fputs("-------------------------------\n", datei);
            counter++;
            verschiebung ++;
        }else{
            fprintf(datei, " %d  %d  %d |  %d  %d  %d |  %d  %d  %d\n", matrix[i - verschiebung][0], matrix[i - verschiebung][1], matrix[i - verschiebung][2], matrix[i - verschiebung][3], matrix[i - verschiebung][4], matrix[i - verschiebung][5], matrix[i - verschiebung][6], matrix[i - verschiebung][7], matrix[i - verschiebung][8]);
        counter ++;
        }  
    }
    fclose(datei);
}








void printMatrix(int** matrix){
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%d ", matrix[i][j]);
        }
    printf("\n");
    }
    return;
}
