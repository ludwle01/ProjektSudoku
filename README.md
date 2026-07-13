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
    * [validate() - Regelüberprüfung](#regelüberprüfung)
    *  [solve() mit Backtracking](#sudoku-lösen-mit-backtracking)
       * [Eignung](#tauglichkeit-vom-backtracking)
       * [4x4 Sudokus](#größere-sudokus-lösen)
    * [createSudoku() - Sudoku-Generierung](#sudoku-generierung)
    * [Donald Knuth - Exact Cover & Lösungsanzahl](#donald-knuth---exact-cover)
        * [Tauglichkeit und Performance](#tauglichkeit-und-performance)
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

Das Einlesen der Rätsel erfolgt aus der Textdatei `inputSudoku.txt`. Damit die Daten erfolgreich verarbeitet werden können, ist folgendes Format einzuhalten:
* **Gittergröße:** Das Rätsel muss exakt 9 Zeilen mit jeweils genau 9 Ziffern beinhalten.
* **Ziffern:** Erlaubt sind die Ziffern von `0` bis `9`. Eine `0` steht dabei für ein leeres beziehungsweise noch unbekanntes Feld im Sudoku.
* **Trennzeichen:** Leerzeichen (` `), senkrechte Striche (`|`) und Trennstriche (`-`) können zur optischen Gliederung des Gitters in der Textdatei verwendet werden, da sie vom Programm automatisch ignoriert werden.
* **Leere Zeilen:** Leerzeilen innerhalb der Datei werden übersprungen und führen zu keinem Abbruch.
Sollten fehlerhafte Zeichen auftreten, zu viele oder zu wenige Einträge pro Zeile existieren oder das Sudoku unvollständig sein (weniger als 9 gültige Zeilen), bricht das Einlesen mit einer passenden Fehlermeldung ab.

### Menüführung
Die Steuerung der Toolbox erfolgt über ein interaktives, textbasiertes Menü im Terminal. Der Anwender hat dabei Zugriff auf folgende Hauptfunktionen:
* **Einlesen:** Laden eines neuen Sudokus aus der Datei `inputSudoku.txt`.
* **Automatisches Lösen & Hinweise:** Das vollständige Lösen des Rätsels oder das Anfordern spezifischer Hinweise für bestimmte Bereiche.
* **Neues Sudoku generieren:** Erstellen eines neuen Rätsels in drei wählbaren Schwierigkeitsgraden.
* **Interaktives Lösen:** Eigenständiges Ausfüllen des Gitters mit integrierter Regelüberprüfung und Motivationshilfen.

### Menüführung


Verfügbare Funktionen
---------------------

### Sudoku einlesen

Die Funktion `read()` ist für das Einlesen des Sudokus aus der Datei `inputSudoku.txt` zuständig und speichert das Gitter in einer 9x9-Matrix ab. Während des Einlesevorgangs wird bereits eine Fehler- und Syntaxprüfung durchgeführt:
* Er kontrolliert, ob ausschließlich gültige Ziffern (`0`-`9`) verwendet werden und genau 9 Einträge pro Zeile existieren.
* Formatierungszeichen wie Striche oder Leerzeichen, die der besseren Lesbarkeit dienen, werden ausgeblendet.
* Nach dem erfolgreichen Einlesen wird das erkannte Sudoku zur Kontrolle direkt in der Konsole ausgegeben.

### Regelüberprüfung
Direkt nach dem Einlesen sowie bei jedem Spielzug während des interaktiven Lösens kommt die Funktion `validate()` zum Einsatz. Sie stellt sicher, dass die aktuelle Matrix den Sudoku-Regeln entspricht:
* Mit temporären Hilfsarrays wird für jede Zeile, jede Spalte und jeden der 3x3-Blöcke kontrolliert, ob eine Ziffer doppelt vorkommt.
* Sobald ein Regelverstoß entdeckt wird, bricht die Prüfung ab und gibt eine präzise Fehlermeldung auf dem Terminal aus (z. B. *"In Block 4 ist eine doppelte Zahl vorhanden."*).

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

### Sudoku-Generierung
Für die Erstellung neuer Rätsel ist die Funktion `createSudoku()` zuständig. Sie erzeugt per Brute-Force-Verfahren ein vollständig ausgefülltes und gültiges 9x9-Sudokugitter, indem zufällige Zahlen platziert und die verbleibenden Felder logisch aufgefüllt werden. 
* **Schwierigkeitsgrade:** Anschließend werden je nach gewähltem Level gezielt Zahlen aus dem Gitter entfernt (Leicht: 40 Felder, Mittel: 50 Felder, Schwer: 55 Felder).
* **Sicherheitsnetz:** Sollte ein Sudoku während der Generierung unlösbar werden oder sich in einer Sackgasse befinden, bricht eine integrierte Abbruchbedingung nach über 500 Fehlversuchen automatisch ab und startet die erstellung sauber von vorn. Das fertige Rätsel wird anschließend ausgegeben.

### Donald Knuth - Exact Cover
Um die mathematische Eindeutigkeit der generierten Rätsel zu garantieren, setzt die Toolbox zusätzlich auf eine vereinfachte Vestion des bekannten Algorithmus X (Exact-Cover-Problem) von Donald Knuth:
* **Die 729x324-Matrix:** Hierbei werden die vier grundlegenden Sudoku-Regeln (Feld-, Zeilen-, Spalten- und Block-Regel) als exaktes Überdeckungsproblem in einer großen binären Matrix modelliert.
* **Lösungsanzahl prüfen:** Nach jedem entfernten Feld in `createSudoku()` prüft die Funktion `getSolutionAmount()`, ob das Rätsel weiterhin exakt eine einzige Lösung besitzt. Ist dies nicht der Fall (Gitter hat keine oder mehrere Lösungen), wird der letzte Schritt rückgängig gemacht.
* **Flexibilität (`doASolve`):** Der Algorithmus kann je nach Parameter entweder ausschließlich die genaue Anzahl der Lösungen zählen oder das Sudoku aktiv lösen und die Lösung abspeichern.

#### Tauglichkeit und Performance
Der Algorithmus von Donald Knuth spielt seine Stärken vor allem bei sehr komplexen Sudokus aus. Selbst bei komplexen Rätseln mit nur 17 vorgegebenen Ziffern (dem Minimum für eine eindeutige Lösung) hat er eine hervorragende Laufzeit. Zwar werden auch leichtere Rätsel zuverlässig gelöst, allerdings geringfügig langsamer als mit dem Brute-Force-Algorithmus. Grund dafür ist, dass bei dem Brute-Force-Ansatz keine komplexe 729x324-Matrix aufgebaut werden muss.

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

- Implementierung des Algorithmus nach Donald Knuth (Exact-Cover-Matrix) zur Lösungssuche
- Sudoku-Generierung (`createSudoku`) für drei verschiedene Schwierigkeitsgrade
- Überprüfung der Lösungsanzahl und Eindeutigkeit (`getSolutionAmount`)

#### Lena: 
- Backtracking Solver inkl. Erweiterung auf Hexadezimal-Sudokus
- Möglichkeit, Lösungen teilweise auszugeben
- Funtool mit Motivationssprüchen

#### Jari:
