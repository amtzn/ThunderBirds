#pragma once

#include "Utils.h"
#include "Board.h"

class Point
{
	int x, y;
	Board* pBoard;

public:
	//C'tor
	Point(int _x = initValue, int _y = initValue, Board* _pBoard = nullptr) : x(_x), y(_y), pBoard(_pBoard) {};

	//This function reutrns the x value of the point
	int getX() const{ return x; };

	//This function reutrns the y value of the point
	int getY() const{ return y; };

	//This function sets the x value according to the received value
	void setX(int _x) {  x = _x; };

	//This function sets the y value according to the received value
	void setY(int _y) { y = _y; };

	//This function sets the board pointer        
	void setBoard(Board* pb) { pBoard = pb; }

	//This function draws the received character on the screen, according to the x and y values
	void draw(char ch, int color, bool isColored) const;

	//This function prints space on the screen according to the x and y values 
	void del() const {
		gotoxy(x, y);
		std::cout << Figures::Empty;
	}

	/*This function gets character and direction, then updates the point data members accordingly, updates the board, 
	 deletes the current character and then prints it according to the new x and y values*/
	void move(Direction dir, char ch, int color, bool isColored, bool isSilented);

	//This function returns the next point according to the received direction
	Point getNextPoint(Direction dir) const;

	//This function returns the next char according to the received direction
	char getNextChar (Direction dir) const;

	//This function overloads the == operator
	bool operator==(const Point& point) const;
};

