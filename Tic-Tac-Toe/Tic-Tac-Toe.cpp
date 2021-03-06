#include "stdafx.h"
#include <iostream>
#include <conio.h> // _getch()
#include <windows.h> // COORD()
#include <stdlib.h> // atoi()
using namespace std;

// O = 0, X = 1, as the "playerCharacter" array below.
enum Position { O = 0, X = 1, Empty = 2 };

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(COORD coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void paintingPlayground()
{
	char title[] = "Developer: Adrian Yordanov";
	char wallCharacter = '*';
	gotoxy(20, 4);
	cout << title;
	for (int i = 20; i <= 50; ++i)
	{
		gotoxy(i, 5);
		cout << wallCharacter;
		gotoxy(i, 8);
		cout << wallCharacter;
		gotoxy(i, 11);
		cout << wallCharacter;
		gotoxy(i, 14);
		cout << wallCharacter;
	}

	for (int i = 5; i <= 14; ++i)
	{
		gotoxy(20, i);
		cout << wallCharacter;
		gotoxy(30, i);
		cout << wallCharacter;
		gotoxy(40, i);
		cout << wallCharacter;
		gotoxy(50, i);
		cout << wallCharacter;
	}
}

void core()
{
	bool currentPlayer = 0;
	bool hasWinner = false;
	char playerCharacters[] = 
	{ 
		'O', 
		'X' 
	};

	Position playground[] =
	{
		Empty, Empty, Empty,
		Empty, Empty, Empty,
		Empty, Empty, Empty
	};

	char playerColors[][10] =
	{
		"color D",
		"color E"
	};

	COORD playerTurnCoords = { 56, 5 };
	COORD playgroundCoords[9] =
	{
		COORD{ 25, 6 }, COORD{ 35, 6 }, COORD{ 45, 6 },
		COORD{ 25, 9 }, COORD{ 35, 9 }, COORD{ 45, 9 },
		COORD{ 25, 12 }, COORD{ 35, 12 }, COORD{ 45, 12 }
	};

	while (true)
	{
		gotoxy(playerTurnCoords);
		system(playerColors[currentPlayer]);
		cout << "It's " << playerCharacters[currentPlayer] << " turn, press a number(1-9)...";
		char key = _getch();
		while ((int)key < 49 || (int)key > 57)
		{
			key = _getch();
		}

		char tempBuffer[1] = { key };
		int wantedPosition = atoi(tempBuffer);
		if (playground[wantedPosition - 1] != Empty)
		{
			continue;
		}

		playground[wantedPosition - 1] = (Position)currentPlayer;
		gotoxy(playgroundCoords[wantedPosition - 1]);
		cout << playerCharacters[currentPlayer];
		if ((playground[0] == (Position)currentPlayer && playground[1] == (Position)currentPlayer && playground[2] == (Position)currentPlayer) ||
			(playground[3] == (Position)currentPlayer && playground[4] == (Position)currentPlayer && playground[5] == (Position)currentPlayer) ||
			(playground[6] == (Position)currentPlayer && playground[7] == (Position)currentPlayer && playground[8] == (Position)currentPlayer) ||
			(playground[0] == (Position)currentPlayer && playground[3] == (Position)currentPlayer && playground[6] == (Position)currentPlayer) ||
			(playground[1] == (Position)currentPlayer && playground[4] == (Position)currentPlayer && playground[7] == (Position)currentPlayer) ||
			(playground[2] == (Position)currentPlayer && playground[5] == (Position)currentPlayer && playground[8] == (Position)currentPlayer) ||
			(playground[2] == (Position)currentPlayer && playground[4] == (Position)currentPlayer && playground[6] == (Position)currentPlayer) ||
			(playground[0] == (Position)currentPlayer && playground[4] == (Position)currentPlayer && playground[8] == (Position)currentPlayer))
		{
			hasWinner = true;
			break;
		}

		if (playground[0] != Empty && playground[1] != Empty && playground[2] != Empty &&
			playground[3] != Empty && playground[4] != Empty && playground[5] != Empty &&
			playground[6] != Empty && playground[7] != Empty && playground[8] != Empty)
		{
			break;
		}

		currentPlayer = !currentPlayer;
	}

	COORD resultCoords = { 56, 6 };
	COORD pressAnyKeyCoords = { 56, 7 };
	gotoxy(resultCoords);
	hasWinner == false ? cout << "No winner." : cout << "Winner: " << playerCharacters[currentPlayer];
	gotoxy(pressAnyKeyCoords);
	system("pause");
}

int main()
{
	paintingPlayground();
	core();
}