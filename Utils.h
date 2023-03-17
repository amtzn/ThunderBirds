#pragma once

#include <iostream>
#include <windows.h>
#include <process.h>

struct Color
{
	constexpr static int GREY = 8;
	constexpr static int LIGHTBLUE = 9;
	constexpr static int LIGHTGREEN = 10;
	constexpr static int LIGHTCYAN = 11;
	constexpr static int LIGHTRED = 12;
	constexpr static int LIGHTMAGENTA = 13;
	constexpr static int YELLOW = 14;
	constexpr static int WHITE = 15;
};

struct Keys {
	constexpr static char ESC = 27;
	constexpr static char Up = 'w';
	constexpr static char Right = 'd';
	constexpr static char Down = 'x';
	constexpr static char Left = 'a';
	constexpr static char Big = 'b';
	constexpr static char Small = 's';
	constexpr static char Stat = 'p';
};

struct shipSize {
	constexpr static int Small = 2;
	constexpr static int Big = 4;
};

struct ScreenSize {
	constexpr static int Width = 25;
	constexpr static int Height = 81;
};

struct Figures {
	constexpr static char BigShip = '#';
	constexpr static char SmallShip = '@';
	constexpr static char VertGhost = '!';
	constexpr static char HorizGhost = '$';
	constexpr static char WanderGhost = '%';
	constexpr static char WinPoint = 'E';
	constexpr static char Wall = 'W';
	constexpr static char Empty = ' ';
	constexpr static char LegendInfo = '&';
	constexpr static char Block = '+';
	constexpr static char pWall = 178;
	constexpr static char Heart = (char)3;
};

struct MoveStatus {
	constexpr static int CantMove = 0;
	constexpr static int Moved = 1;
	constexpr static int HitEndPoint = 2;
	constexpr static int HitBlock = 3;
	constexpr static int HitGhost = 4;
	constexpr static int HitShip = 5;
};

struct ShipStatus {
	constexpr static int InGame = 0;
	constexpr static int NotInGame = 1;
};

enum class Direction { Up, Down, Left, Right, Stat };

enum class GameMode { Standard, Record, Loaded };

constexpr static int initValue = -1;
constexpr static int FullGameLength = 3;

void gotoxy(int, int);
void clrscr();
void makeBoardNamesFile();
void hide_cursor();
void setTextColor(int colorToSet);