int solve(int row int column){
    int number = 1; // zu testende Zahl

	if (column == 9) { // am Ende einer Zeile angekommen
		column = 0; // am Anfang der naechsten Zeile geht es weiter
		row++;
	}

	if (row == 9){ // letzte Zeile (Zeile 8) beendet
		return 1;  // also fertig
    }

	while (number < 10) { // Zahlen nacheinander testen
		if (is_valid(row, column, number)) { // wenn die Zahl passt
			
            grid[row][column] = number; // Zahl wird eingetragen
            // ... und das Gitter an der naechsten Position angeschaut
			if (solve_cell(row, column + 1)){ // rekursiver Aufruf
				return 1;
            }
		}

		grid[row][column] = 0; // Eintrag 0, wenn die Zahl nicht passt

		number++; // naechste Zahl ausprobieren, neuer Schlefendurchlauf
	}

	return 0; // wenn keine Zahl passt: 0 wird zurück gegeben
}