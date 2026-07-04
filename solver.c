#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

int solver(int **grid, int row, int column)
{
	int number = 1; // zu testende Zahl

	if (column == 9)
	{				// am Ende einer Zeile angekommen
		column = 0; // am Anfang der naechsten Zeile geht es weiter
		row++;
	}

	if (row == 9)
	{			  // letzte Zeile (Zeile 8) beendet
		return 1; // also fertig
	}

	while (number < 10)
	{ // Zahlen nacheinander testen
		if (is_valid(grid, row, column, number))
		{ // wenn die Zahl passt

			grid[row][column] = number; // Zahl wird eingetragen
										// ... und das Gitter an der naechsten Position angeschaut
			if (solve_cell(row, column + 1))
			{ // rekursiver Aufruf
				return 1;
			}
		}

		grid[row][column] = 0; // Eintrag 0, wenn die Zahl nicht passt

		number++; // naechste Zahl ausprobieren, neuer Schlefendurchlauf
	}

	return 0; // wenn keine Zahl passt: 0 wird zurück gegeben
}

int is_valid(int **grid, int row, int column, int number)
{

	int i; // Zaehlvariablen einfuehren
	int j;

	for (i = 0; i < 9; i++)
	{
		// alle Spalten i der Zeile row durchgehen
		if (i != column)
		{ // alle Felder der Zeile außer das betrachtete abchecken
			if (grid[row][i] == number)
			{			  // wenn die Zahl schonmal vorkommt...
				return 0; //... kann sie nicht in das Feld kommen
			}
		}
		// alle Zeilen i der Spalte column durchgehen
		if (i != row)
		{ // alle anderen Felder der Spalte abchecken
			if (grid[i][column] == number)
			{			  // wenn die Zahl schonmal vorkommt...
				return 0; // ... kann sie nicht nochmal in diese Spalte
			}
		}
	}

	int fr = (row / 3) * 3; // jetzt das 3*3 Feld abchecken
	int fc = (column / 3) * 3;

	for (i = fr; i < fr + 3; i++)
	{ // i laeuft ueber die Zeilenindizes vom 3*3 Feld
		for (j = fc; j < fc + 3; j++)
		{ // j ueber die Splatenindizes
			if (i != row || j != column)
			{ // alle anderen Felder im 3*3 Feld betrachten
				if (grid[i][j] == number)
				{			  // Wenn der Wert schonmal vorkommt...
					return 0; // ... kann er nicht auch in das zu testende Feld!
				}
			}
		}
	}

	// wenn bisher noch nichts dagegen spricht...
	return 1; //... darf die Zahl in das betrachtete Feld
}
