#pragma once

#include "Utils.h"

struct ExitScreen {
	constexpr static int BarWidth = 64;
	constexpr static int InitCol = 8;
	constexpr static int UpRow = 20;
	constexpr static int DownRow = 21;
	constexpr static char BarFigure = '@';
};

class Menu
{
public:

	//This function prints the entry screen for the game
	void printEnteryScreen() const;

	//This function prints the game menu
	void printMenu() const;
	
	//This function prints the keys and instructions menu 
	void printKeysAndInst() const;

	//This function prints the exit screen from the game
	void printExit() const;
};

