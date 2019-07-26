#include<iostream>
#include "header.h"
#include<algorithm>
#include <ctime>
using namespace std;
char field[10];								// Zwar bereits in der Header-Datei deklariert, wird aber erst hier definiert (dimensioniert)!

void AI(int difficulty) {
	srand((unsigned)time(nullptr));

	if (difficulty == 1) {					// Easy
		int check = rand() % 3;
		if (check != 1)	{
			for (int i = 1; i < 10; i++) {	// Check if AI can win
				if (field[i] == ' ') {
					field[i] = 'O';
					if (checkWin('O')) {
						return;
					}
					else {
						field[i] = ' ';
					}
				}
			}
		}
		else if (check != 2) {
			for (int i = 1; i < 10; i++) {	// Check if Player can win
				if (field[i] == ' ') {
					field[i] = 'X';
					if (checkWin('X')) {
						field[i] = 'O';
						return;
					}
					else {
						field[i] = ' ';
					}
				}
			}
		}
		while (true) {
			int i = rand() % 9 + 1;
			if (field[i] == ' ')
			{
				field[i] = 'O';
				return;
			}
		}
	}
	else if (difficulty == 2) {				// Medium
		int check = rand() % 2;
		if (check == 1) {
			for (int i = 1; i < 10; i++) {	// Check if AI can win
				if (field[i] == ' ') {
					field[i] = 'O';
					if (checkWin('O')) {
						return;
					}
					else {
						field[i] = ' ';
					}
				}
			}
		}
		else if (check == 2) {
			for (int i = 1; i < 10; i++) {	// Check if Player can win
				if (field[i] == ' ') {
					field[i] = 'X';
					if (checkWin('X')) {
						field[i] = 'O';
						return;
					}
					else {
						field[i] = ' ';
					}
				}
			}
		}
		while (true) {
			int i = rand() % 9 + 1;
			if (field[i] == ' ') {
				field[i] = 'O';
				return;
			}
		}
	}
	else if (difficulty == 3) {				// Hard
		for (int i = 1; i < 10; i++) {		// Check if AI can win
			if (field[i] == ' ') {
				field[i] = 'O';
				if (checkWin('O')) {
					return;
				}
				else {
					field[i] = ' ';
				}
			}
		}

		for (int i = 1; i < 10; i++) {		// Check if Player can win and stop it
			if (field[i] == ' ') {
				field[i] = 'X';
				if (checkWin('X')) {
					field[i] = 'O';
					return;
				}
				else {
					field[i] = ' ';
				}
			}
		}

		// Select middle field if possible (Feld '5').
		if (field[5] == ' ') {									//<-- Neu: IMMER das mittlere Feld abfragen!
			field[5] = 'O';
			return;
		}

		// Select corner fields if possible (die Eckfelder durchprobieren).
		int code[4] = { 1, 3, 7, 9 };							//<-- NEU: die 4 Ecken.
		srand(unsigned(time(0)));								//<-- NEU: ini Random
		random_shuffle(code, code + 3);							//<-- NEU: Reihenfolge der Ecken (zufällig) vertauschen.

		for (int i = 0; i < 4; i++) {							//<-- Neu: nur die 4 Ecken prüfen!
			int j = code[i];									//<-- Neu: KEINE Wiederholungen!

			if (field[j] == ' ') {								//j war i!
				field[j] = 'O';									//j war i!
				return;
			}
		}

		// Select further random fields if possible (die restlichen Felder durchprobieren).
		int code2[4] = { 2, 4, 6, 8 };							//<-- NEU: die 4 Ecken.
		srand(unsigned(time(0)));								//<-- NEU: ini Random
		random_shuffle(code2, code2 + 3);							//<-- NEU: Reihenfolge der Ecken (zufällig) vertauschen.

		for (int i = 0; i < 4; i++) {							//<-- Neu: nur die 4 Ecken prüfen!
			int j = code2[i];									//<-- Neu: KEINE Wiederholungen!

			if (field[j] == ' ') {								//j war i!
				field[j] = 'O';									//j war i!
				return;
			}
		}
	}
	else {
		return;
	}
}
