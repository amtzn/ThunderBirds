#pragma once
#include "Utils.h"
#include <iostream>

class Board
{
	char board[ScreenSize::Width][ScreenSize::Height]; 

	//This function receives character and prints it in the matching color 
	void setRightColor(char ch) const;

public:

	//This function returns the character in the board according to the received x and y values 
	char get(int x, int y) const { return board[y][x]; }

	//This function sets the received character in the board according to the received x and y values 
	void set(int x, int y, char c) { board[y][x] = c; }

	//This function recevies boolean value, and prints colored/not colored board accordingly 
	void printBoard(bool isColored) const;
};
