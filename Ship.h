#pragma once

#include "Point.h"

class Ship
{
	enum { SIZE = 4 };
	Point body[SIZE];
	Board* pBoard;
	const char type;
	const char figure;
	Direction dir;
	int size;
	int maxWeight;
	int color;
	bool isColored;
	bool isSilented;

	//This function returns true if the ships next move is valid according to the direction 
	bool isNextMoveValid() const;

	//This function returns if true if the received char is a ghost char and false otherwise
	bool isGhost(char ch) const;

public:

	//C'tor
	Ship(Board* _pBoard, char _type, char _figure, int _color, bool _isColored = false, bool _isSilented = false);

	//This function inserts the received x and y values in the next "empty" point index
	void init(int x, int y);

	//This function returns the figure of the ship
	char getFigure() const{ return figure; }

	//This function returns the ship type
	char getType() const { return type; }

	//This function returns the max weight that the ship can carry/push
	int getMaxWeight() const { return maxWeight; }
	
	//This function sets new direction for the ship
	void setDirection(Direction newDir) { dir = newDir; }

	//This function returns the direction of the ship
	Direction getDirection() const { return dir; }

	//This function moves the ship according to the direction if possible and returns indication accordingly
	int move();

	//This function returns the next point according to the received direction
	Point getNextPoint(Direction dir) const;

	//This function deletes the ship from the board and from the screen
	void remove() const;
};


