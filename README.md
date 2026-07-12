Sudoku Rätsel Toolbox
================================
### Inhaltsverzeichnis

1.  [Zweck der Toolbox](#zweck-dieser-toolbox)
2.  [Bedienungsanleitung](#hinweise-zur-benutzung)
    *  [Spielregeln](#sudoku-spielregeln)
    *  [Eingabe Format](#format-der-eingabe)
    *  [Menüführung](#menüführung)
3.  [Verfügbare Funktionen](#verfügbare-funktionen)
    *  [read()](#sudoku-einlesen)
    *  [solve() mit Backtracking](#sudoku-lösen-mit-backtracking)
       * [Eignung](#tauglichkeit-vom-backtracking)
       * [4x4 Sudokus](#größere-sudokus-lösen)
    *  [Lisas Algorithmus](#lisasüberschrift)
    *  [Interaktives Lösen](#interaktives-lösen)
       *  [Jari dein Part](#jarisüberschrift)
       *  [Hinweise ausgeben](#spezifische-hinweise-anfordern)
       *  [Funtool](#motivationshilfe)
4.  [Ausstehende Erweiterungen](#coming-soon)
5.  [Autoren](#wer-hat-was-gemacht)

Zweck dieser Toolbox
--------------------
Diese Toolbox wurde erstellt, um einen Benutzer beim Lösen von Sudoku Rätseln in leichter bis mittlerer Schwierigkeit zu unterstützen. 
Es können Sudokus eingelesen, vollständig gelöst und Hinweise gegeben werden. Außerdem können neue Rätsel erstellt werden und der Benutzer kann 
interaktiv ein Sudoku lösen.

Hinweise zur Benutzung
----------------------

### Sudoku Spielregeln
Dieses Tool richtet sich nach den herkömmlichen Sudoku Spielregeln: 
Das vorgegebene 9x9 Rätselgitter soll derart mit den Ziffern von 1 bis 9 aufgefüllt werden, 
dass in jeder Zeile, jeder Spalte und jeder 3x3 Box jede dieser Ziffer von 1 bis 9 genau einmal vorkommt.

### Format der Eingabe


### Menüführung


Verfügbare Funktionen
---------------------

### Sudoku einlesen

### Sudoku lösen mit Backtracking

#### Tauglichkeit vom Backtracking
Der Backtracking Algorithmus ist gut geeignet, um leichte bis mittelschwere 3x3 Sudokus zu lösen.
Es wird genau eine Lösung ausgegeben. Der Algorithmus lässt sich bei Bedarf einfach nachvollziehen.
#### Größere Sudokus lösen
In dem separaten Projektordner ProjekSudokuHex/ ist ein spezielles main Programm hinterlegt, um 4x4 
Sudoku Rätsel zu lösen. Zusätzlich zu den Ziffern 1 bis 9 wird in diesen Rätseln mit der Ziffer 0 sowie
den Buchstaben a bis f gearbeitet. Bei der Eingabe muss berücksichtigt werden, dass "." an unbekannten 
Positionen steht, anstatt der Ziffer 0. Ansonsten nutzt das Programm den gleichen Backtracking Algorithmus 
wie im Standard 3x3 Programm, es können jedoch nur Rätsel mit niedrigem Schwierigkeitsgrad geöst werden. 

### lisasüberschrift

### Interaktives Lösen

#### jarisüberschrift

#### Spezifische Hinweise anfordern
Möchte ein Benutzer nicht die vollständige Lösung einsehen, sondern lediglich einen spezifischen Teil davon,
so kann er über die Menüführung.... zu einer weiteren Auswahl gelangen: Es kann die Lösung einer bestimmte Zeile, 
einer gewünschten 3x3 Box oder eines einzelnen Kästchens ausgegeben werden.

#### Motivationshilfe
Zweck dieser Toolbox ist es, dem Benutzer ein vergnügtes Rätselraten zu ermöglichen. 
Deshalb können nicht nur Sudokus maschinell gelöst werden, sondern der Benutzer kann sich auch motivieren lassen,
sein Rätsel eigenständig zu meistern. Über die Menüoption .... kann dieses Tool erreicht werden.
Dem Anwender wird ein zufälliger Spruch aus einem 10-teiligen Pool ausgegeben, der zum Weiterrätseln animieren soll.

Coming soon
-----------
Benutzer dürfen auf die ständige Erweiterung unserer Toolbox hoffen. Angedacht sind u.a. das effizientere Lösen 
von 4x4 und noch größeren Sudokus. Zukünftig sollen auch einzelne Spalten ausgegeben werden können, um dem Benutzer
noch mehr Optionen für spezifische Hinweise zur Verfügung zu stellen.
....offene Ideen

Wer hat was gemacht
-------------------
#### Lisa:

#### Lena: 
- Backtracking Solver inkl. Erweiterung auf Hexadezimal-Sudokus
- Möglichkeit, Lösungen teilweise auszugeben
- Funtool mit Motivationssprüchen

#### Jari:
