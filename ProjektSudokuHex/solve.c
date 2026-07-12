#include "sudoku.h" 

int solve(int row, int column, int **sudoku){

	if (column == SIZE) { // am Ende einer Zeile angekommen
		column = 0; // am Anfang der naechsten Zeile geht es weiter
		row++;
	}

	if (row == SIZE){ // letzte Zeile beendet
		return 1;  // also fertig
    }

	if (sudoku[row][column] != EMPTY) { // besetzte Felder ueberspringen
        return solve(row, column+1, sudoku);
    }

	for(int number = 0; number < SIZE; number++) { // sonst: Zahlen nacheinander testen
		if (validate_cell(row, column, number, sudoku)) { // wenn die Zahl passen wuerde
			sudoku[row][column] = number; // Zahl eintragen
            // ... und das Gitter an der naechsten Position angeschaut
			if(solve(row, column + 1, sudoku)){ // rekursiver Aufruf
				return 1;
            }
		}

		sudoku[row][column] = EMPTY; // Eintrag resetten, wenn die Zahl nicht passt
	}
	
	// 
	return 0; 
}

int validate_cell(int row, int column, int number, int **sudoku){

	int i; // Zaehlvariablen einfuehren
	int j; 

	for (i = 0; i < SIZE; i++) { 
		// alle Spalten i der Zeile row durchgehen 
		if (i != column && sudoku[row][i] == number){ // alle Felder der Zeile außer das betrachtete abchecken
			// wenn die Zahl schonmal vorkommt...
			return 0; //... kann sie nicht in das Feld kommen
		}
		// alle Zeilen i der Spalte column durchgehen 
		if (i != row && sudoku[i][column] == number){ // alle anderen Felder der Spalte abchecken
			// wenn die Zahl schonmal vorkommt...
			return 0; // ... kann sie nicht nochmal in diese Spalte
		}
	}

	int fr = (row/BLOCK)*BLOCK; // jetzt das kleine Feld abchecken
	int fc = (column/BLOCK)*BLOCK;

	for (i=fr; i<fr+BLOCK; i++){ // i laeuft ueber die Zeilenindizes vom 3*3 Feld
		for (j=fc; j<fc+BLOCK; j++){ // j ueber die Splatenindizes
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
