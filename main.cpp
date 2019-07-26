// Tutorial #014: TicTacToe mit Computergegner (von Pilzschaf)
// QUELLE: https://www.youtube.com/watch?v=WUketL_86w0
// HINT: Gewinnstrategie: als erstes die Mitte besetzen ('5' eingeben), dann möglichst die Ecken besetzen (1,3,7,9).

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>		// für random_shuffle
#include "header.h"			// eingebundene Header-Datei.
using namespace std;
void singlePlayer(), multiPlayer(), Help();
bool checkFull(), Fehler(0), Start(0), Wechsel(0), Single(true), Config(true), Ende(0);
int difficulty = 0;
char keyInput(bool x, bool y), input = ' ', inDiff = ' ', inStart = ' ';

void resetField() {
	for (int i = 0; i < 10; i++)
	{ field[i] = ' '; }
}

void menu() {
	while (true) {
		Single = false;
		Config = true;
		resetField();
		system("cls");
		char inMenu = ' ';

		cout << "\n"
			<< " TIC TAC TOE\n\n"
			<< " MENU\n ====\n"
			<< " 1: Singleplayer\n"
			<< " 2: Multiplayer\n"
			<< " 3: Help\n"
			<< " q: Quit (Beenden)\n";

		if(Fehler) cout << "\n Falsche Eingabe! Bitte noch einmal: "; else cout << "\n Eingabe: ";
		Fehler = false;
		cin.clear(); cin.ignore(cin.rdbuf()->in_avail());		// Fängt Mehrfacheingaben ab.
		cin >> inMenu;

		if (inMenu == '1')singlePlayer();
		else if (inMenu == '2')multiPlayer();
		else if (inMenu == '3')Help();
		else if (inMenu == 'q')exit(0);
		else Fehler = true;
	}
}

void drawField() {
	system("cls");
	cout << "\n    TIC  TAC  TOE";
	if (Single) cout << " (Singleplayer - Level " << inDiff << ")";
	cout << "\n\n    o-----------o" << endl
		<< "    | " << field[1] << " | " << field[2] << " | " << field[3] << " |" << endl
		<< "    |---|---|---|" << endl
		<< "    | " << field[4] << " | " << field[5] << " | " << field[6] << " |" << endl
		<< "    |---|---|---|" << endl
		<< "    | " << field[7] << " | " << field[8] << " | " << field[9] << " |" << endl
		<< "    o-----------o" << endl;
}

void singlePlayer() {
	Single = true;
	if (Config) {
		Config = false;

		do {
			system("cls");
			cout << "\n TIC TAC TOE (Singleplayer)\n";
			cout << "\n LEVEL\n =====\n 1: Easy\n 2: Medium\n 3: Hard\n q: Quit (Zurueck zum Menue)\n";
			if (Fehler) cout << "\n Falsche Eingabe! Bitte noch einmal: "; else cout << "\n Eingabe: ";
			Fehler = false;
			cin.clear(); cin.ignore(cin.rdbuf()->in_avail());	// Fängt Mehrfacheingaben ab.
			cin >> inDiff;

			if (inDiff == '1') difficulty = 1;
			else if (inDiff == '2') difficulty = 2;
			else if (inDiff == '3') difficulty = 3;
			else if (inDiff == 'q') return;
			else Fehler = true;
		} while (Fehler == true);

		do {
			system("cls");
			cout << "\n TIC TAC TOE (Singleplayer)\n";
			cout << "\n Wer soll anfangen?\n\n 1: Spieler\n 2: Computer\n q: Quit (Zurueck zum Menue)\n";
			if (Fehler) cout << "\n Falsche Eingabe! Bitte noch einmal: "; else cout << "\n Eingabe: ";
			Fehler = false;
			cin.clear(); cin.ignore(cin.rdbuf()->in_avail());	// Fängt Mehrfacheingaben ab.
			cin >> inStart;
			if (inStart == '1') Start = true;
			else if (inStart == '2') Start = false;
			else if (inStart == 'q')menu();
			else Fehler = true;
		} while (Fehler == true);
	}

	drawField();
	
	if (Start)cout << "\n Der Spieler beginnt...\n"; else cout << "\n Der Computer beginnt...\n";

	if (inStart == '1') {
		Start = true;
		Wechsel = true;
	}
	else {
		Start = false;
		Wechsel = false;
	}

	while (true) {
		if (Wechsel) {
			input = keyInput(true, true);						// Der Spieler ist dran.
		}
		else {
			AI(difficulty);										// Der Computer ist dran.
		}
		drawField();

		if (checkWin('O')) {
			cout << "\n Du hast leider verloren!\n\n";
			Ende = true; break;									// statt "return".
		}

		if (checkWin('X')) {
			cout << "\n Du hast gewonnen! Glueckwunsch!\n\n";
			Ende = true; break;									// statt "return".
		}

		if (checkFull()) {
			cout << "\n Unentschieden!\n\n";
			Ende = true; break;									// statt "return".
		}

		Wechsel = !Wechsel;										// Seitenwechsel (Spieler / Computer).
	}

	if (Ende) {
		// Das gleiche Spiel noch einmal?
		char inWeiter = ' ';
		cout << "\n Das gleiche Spiel noch einmal (abwechselnd)?\n\n"
			<< " 1: JA - weiter spielen!\n"
			<< " 2: NEIN - zurueck zum Menue.\n\n"
			<< " Eingabe: ";
		cin.clear(); cin.ignore(cin.rdbuf()->in_avail());		// Fängt Mehrfacheingaben ab.
		cin >> inWeiter;

		if (inWeiter == '1') {
			resetField();
			Start = !Start;

			if (Start) {
				cout << "\n Du beginnst!";
				inStart = '1';
			}
			else {
				cout << "\n Der Computer beginnt!";
				inStart = '2';
			}
			singlePlayer();
		}
		else {
			Config = true;
			menu();
		}
	}
}

void multiPlayer() {
	bool Single = false, Ende = false, player1Turn = true;
	char input = ' ', inStart = ' ';
	while (true) {
		drawField();
		if (checkWin('X')) {
			cout << "\n Spieler 1 hat gewonnen! Glueckwunsch!\n\n";
			Ende = true; break;
		}
		else if (checkWin('O'))	{
			cout << "\n Spieler 2 hat gewonnen! Glueckwunsch!\n\n";
			Ende = true; break;
		}
		if (checkFull()) {
			cout << "\n Unentschieden!\n\n";
			Ende = true; break;
		}
		input = keyInput(player1Turn, Single);
		if (input == 'q') return;

		player1Turn = !player1Turn;
	}
	if (Ende) {
		// Das gleiche Spiel noch einmal?
		char inWeiter = ' ';
		cout << "\n Das gleiche Spiel noch einmal (abwechselnd)?\n\n"
			<< " 1: JA - weiter spielen!\n"
			<< " 2: NEIN - zurueck zum Menue.\n\n"
			<< " Eingabe: ";
		cin.clear(); cin.ignore(cin.rdbuf()->in_avail());		// Fängt Mehrfacheingaben ab.
		cin >> inWeiter;

		if (inWeiter == '1') {
			resetField();
			multiPlayer();
		}
		else {
			menu();
		}
	}
}

void Help() {
	system("cls");
	cout << "\n TIC TAC TOE\n\n HELP\n ====\n\n"
		<< " Singleplayer:\n -------------\n In Singleplayermode you play against the Computer.\n\n"
		<< " Multiplayer:\n ------------\n In Multiplayermode you play against a second player.\n Input switches between X and O.\n"
		<< " You can also play this mode, if you want to test new tactics or just want to play against yourself.\n\n"
		<< " Controls:\n ---------\n To choose a field you must enter a number between 1 and 9.\n"
		<< " The first field is in the top left corner. The second right next to it etc.\n"
		<< " With 'q' you always return to the menu or the program will be closed.\n - - -\n";
	cout << "\n Zurueck zum Menue: Bitte eine Taste druecken: ";
	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());			// Fängt Mehrfacheingaben ab.
	cin >> input;
}

char keyInput(bool x, bool y) {
	while (true) {
		if (y) {
			cout << "\n\n Deine Eingabe (X): ";
		}
		else {
			if (x) cout << "\n\n Eingabe Spieler 1 (X): "; else cout << "\n\n Eingabe Spieler 2 (O): ";
		}
		char input = ' ';
		cin.clear(); cin.ignore(cin.rdbuf()->in_avail());		// Fängt Mehrfacheingaben ab.
		cin >> input;
		int inputNumber = input - '0';							// Die Eingabe (char) umwandeln in Integer.
		
		if (inputNumber > 9 || inputNumber < 1)	{
			if (input == 'q') {
				menu();
			}
			else {
				drawField();
				cout << "\n Falsche Eingabe! Bitte nur Zahlen von 1 bis 9.";
			}
		}
		else if (field[inputNumber] != ' ')	{
			drawField();
			cout << "\n Dieses Feld ist bereits besetzt!";
		}
		else {
			if (x)
				field[inputNumber] = 'X';
			else
				field[inputNumber] = 'O';
			return input;
		}
	}
}

bool checkWin(char sign) {
	if (field[1] == sign && field[2] == sign && field[3] == sign || field[1] == sign && field[4] == sign && field[7] == sign || field[1] == sign && field[5] == sign && field[9] == sign\
		|| field[2] == sign && field[5] == sign && field[8] == sign || field[3] == sign && field[6] == sign && field[9] == sign || field[3] == sign && field[5] == sign && field[7] == sign\
		|| field[4] == sign && field[5] == sign && field[6] == sign || field[7] == sign && field[8] == sign && field[9] == sign) {
		return true;
	}
	return false;
}

bool checkFull() {
	for (int i = 1; i <= 9; i++) {
		if (field[i] == ' ') {
			return false;
		}
	}
	return true;
}

// Ganz nebenbei...............................................................................
int max(int a, int b) {						// Geniale Formulierung zum Vergleich zweier Werte.
	return a > b ? a : b;					// Gibt die größere von 2 Variablen (a, b) aus.
}	// Erklärung: "return" an Stelle von "cout <<"! "a < b ?" = ist a größer als b? Wenn ja, gib "a" aus, sonst "b".

int main()
{
	srand((unsigned)time(nullptr));
	menu();
	//system("pause");
	return 0;
}
