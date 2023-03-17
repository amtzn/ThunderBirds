#pragma once

#include "Point.h"
#include <vector>

class Block
{
	std::vector<Point> body;
	Board* pBoard;
	int size;
	const char figure;
	int color;
	bool isColored;
	bool isSilented;

public:

	//C'tor
	Block(Board* _pBoard, char _figure, int _color, bool _isColored, bool _isSilented = false) : pBoard(_pBoard), size(0), figure(_figure), color(_color), isColored(_isColored), isSilented(_isSilented) {}

	//This function is initializing the block recursively according to the received x and y values
	void init(int x, int y);

	//This function returns the figure of the block
	char getFigure() const { return figure; }

	//This function returns the size of the block
	int getSize() const { return size; }

	//This function checks if the block can fall and return indication accordingly
	char canFall() const;

	//This function moves the block according to the direction 
	void move(Direction dir);

	//This function return true if the received point is in the block vector, and false otherwise
	bool isPointInBlock(const Point& point) const;

	//This function prints the block on the screen and updates the block in the board
	void draw() const;

	//This function deletes the block from the board and from the screen
	void remove() const;

	//This function returns point by reference according to the index received
	const Point& getBlockPoint(int i) const { return body[i]; }
};

