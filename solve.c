#include <stdio.h>
#include <stdlib.h>
#include "header.h" 

int solve(int row, int column, int sudoku[9][9]){

	if (column == 9) { // am Ende einer Zeile angekommen
		column = 0; // am Anfang der naechsten Zeile geht es weiter
		row++;
	}

	if (row == 9){ // letzte Zeile (Zeile 8) beendet
		return 1;  // also fertig
    }

	if (sudoku[row][column] != 0) { // besetzte Felder ueberspringen
        return solve(row, column + 1, sudoku);
    }

	for(int number = 1; number < 10; number++) { // sonst: Zahlen nacheinander testen
		if (validate_cell(row, column, number, sudoku)) { // wenn die Zahl passen wuerde
			
            sudoku[row][column] = number; // Zahl eintragen
            // ... und das Gitter an der naechsten Position angeschaut
			if(solve(row, column + 1, sudoku)){ // rekursiver Aufruf
				return 1;
            }
		}

		sudoku[row][column] = 0; // Eintrag resetten, wenn die Zahl nicht passt
	}

	return 0; // wenn keine Zahl passt: 0 wird zurück gegeben
}

int validate_cell(int row, int column, int number, int sudoku[9][9]){

	int i; // Zaehlvariablen einfuehren
	int j; 

	for (i = 0; i < 9; i++) { 
		// alle Spalten i der Zeile row durchgehen 
		if (i != column){ // alle Felder der Zeile außer das betrachtete abchecken
			if (sudoku[row][i] == number){ // wenn die Zahl schonmal vorkommt...
				return 0; //... kann sie nicht in das Feld kommen
			}
		}
		// alle Zeilen i der Spalte column durchgehen 
		if (i != row){ // alle anderen Felder der Spalte abchecken
			if (sudoku[i][column] == number){ // wenn die Zahl schonmal vorkommt...
				return 0; // ... kann sie nicht nochmal in diese Spalte
			}
		}
	}

	int fr = (row/3)*3; // jetzt das 3*3 Feld abchecken
	int fc = (column/3)*3;

	for (i=fr; i<fr+3; i++){ // i laeuft ueber die Zeilenindizes vom 3*3 Feld
		for (j=fc; j<fc+3; j++){ // j ueber die Splatenindizes
			if (i!=row || j!=column){ // alle anderen Felder im 3*3 Feld betrachten
				if (sudoku[i][j] == number){ // Wenn der Wert schonmal vorkommt...
					return 0; // ... kann er nicht auch in das zu testende Feld!
				}
			}
		}
	}

	// wenn bisher noch nichts dagegen spricht...
	return 1; //... darf die Zahl in das betrachtete Feld

}
