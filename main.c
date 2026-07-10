#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h" 

int main() 
{
printf("Hi friendly user!\nI am Mister Masterbrain, your personal assistant for solving Sudoku puzzles!\nHow can I support you today?\n");
printf("1: Solve sudoku\n 2: Demand hint for your sudoku\n 3: Check if your sudoku is solveable\n 4: Get motivational support\n Your choice: ");

int option; // user tippt gewünschte Option ein
int eingabe = scanf("%d", &option);

if(eingabe!=1 || option<1 || option>4) 
{ // invalider Input
    printf("Sorry, Mister Masterbrain cannot help you with that! Try again and choose a number between 1 and 4!\n");
    return EOF;
}

if(option!=4){ // in fast allen Fällen braucht man das Ziel Sudoku
    printf("Mister Masterbrain will refer to the puzzle in file 'inputSudoku.txt' of this project folder.\n Change this puzzle to solve a specific sudoku. \n");
    int** test = read(); // Einlesen aus Datei
    if (test == NULL) { // Fehler beim Einlesen
        fprintf(stderr, "Sudoku could not be read from file 'inputSudoku.txt'\n");
        return 1; 
    }

    if(validate(test)){ // Fehler in der Rätsel Vorlage?
        return 1; // Abbruch, wenn fehlerhafte Vorlage
    }else{ // sonst geht es weiter
        printf( "No missmatch in your puzzle.\n");
    }

    // Sudoku schonmal komplett lösen
    printf("|\n|\nMister Masterbrain is thinking...\n|\n|\n");
    solve(0,0,test); // Lösung ab (0,0), also komplett
    if(validate(test)){ //Fehler in der gefundenen Lösung?
        printf( "Mister Masterbrain could not solve the puzzle... If HE can't, it's simply impossible!\n");
        return 1;
    }else{        
        printf("Mister Masterbrain successsfully solved your Sudoku...\n");
    }

    int option2; // schonmal alles mögliche deklarieren
    int eingabe2;
    int eingabe3;
    int eingabe4;
    int row;
    int column;

    switch(option){
        
        case 1: // ganzes Sudoku ausgeben
            printf("Here comes the whole solution of your puzzle:\n"); 
            printMatrix(test);    
            break; 
        case 2: // Tipp, also nur einen Teil ausgeben
            printf("Choose an option:\n 1: Show specific row\n 2: Show specific 3x3 box\n 3: Show single field\n Your choice: ");
            eingabe2 = scanf("%d", &option2); // user darf nochmal aussuchen

            if(eingabe2!=1 || option2<1 || option2>3) { // invalider Input
                printf("Sorry, Mister Masterbrain cannot help you with that! Try again and choose a number between 1 and 3!\n");
                return 1;
            }

            printf("%d\n", option2);

            switch(option2){
                case 1:
                    printf("Enter row from 1 to 9: Row ");
                    eingabe3 = scanf("%d", &row);
                    if(eingabe3!=1 || row<1 || row>9) { // invalider Input
                        printf("Sorry, this row does not exist!\n");
                        return 1;
                    }
                    printRow(test[row-1]);
                    break;
                case 2:
                    printf("Enter box from 1 (top left), 2 (top middle).... to 9 (bottom right): Box ");
                    eingabe3 = scanf("%d", &row);
                    if(eingabe3!=1 || row<1 || row>9) { // invalider Input
                        printf("Sorry, this box does not exist!\n");
                        return 1;
                    }
                    printBox(test, row);
                    break;
                case 3:
                    printf("Enter row (1-9) of the aimed field: ");
                    eingabe3 = scanf("%d", &row);
                    printf("Enter column (1-9) of the aimed field: ");
                    eingabe4 = scanf("%d", &column);
                    if(eingabe3!=1 || eingabe4!=1 || row<1 || row>9 || column<1 || column>9) { // invalider Input
                        printf("Sorry, this field does not exist!\n");
                        return 1;
                    }
                    printf("Field[%d][%d] needs to be filled with number %d.\n", row, column, test[row-1][column-1]);
            }
            break;
        default: // Lösbarkeit wurde schon geklärt
            printf("Mister Masterbrain has solved that puzzle, it is possible!\n");
            break;
    }

    //_- - - - - - - - - - - TO DO: output(test)
    printf("Find your sudoku's solution in file 'outputSudoku.txt' in the current folder.\n")
    printf("Provided by Mister Masterbrain, your personal sudoku assistant.\n"); // Werbung für's eigene Programm immer gut
   
    // Speicher befreien
    for (int i = 0; i < 9; i++) 
    {
        free(test[i]);
    }
    free(test);

}else{ // unnötige Zusatzoption 4
    motivateMe(); // dummer Spruch zur "Motivation"
}


}
