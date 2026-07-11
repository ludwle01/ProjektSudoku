// unnötige Zusatzoption des Sudoku Solvers
#include <math.h>
#include <time.h>
#include "sudoku.h" 

void motivateMe(void){
    char arr[10][100] = {"Wo andere nur Kaestchen sehen, erkennst du bald das Muster.\n", 
        "Sudoku ist kein Gluecksspiel, sondern ein Triumph der Geduld.\n",
        "Ein leeres Feld ist keine Huerde, sondern eine Einladung zum Denken.\n",
        "Ein echter Optimist schreibt sofort mit Kugelschreiber!\n",
        "Das Sudoku kennt die Loesung schon - du musst sie nur entdecken.\n",
        "Gib nicht auf. Dann schreib lieber eine 10 ins Kaestchen :)\n",
        "Ein Fehler, und du musst von vorne anfangen. hehe.\n",
        "Es ist loesbar! Mehr brauchst du nicht zu wissen.\n",
        "No brain? No gain!\n",
        "Je mehr Zahlen du rausfindest, desto einfacher wird es.\n"
    };
    srand(time(NULL));
    int choose = rand()%10; // zufällig einen Spruch auswählen
    printf( "%s",arr[choose]);
}