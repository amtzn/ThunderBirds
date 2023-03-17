#pragma once

#include "Point.h"

class Ghost
{
	Point body; 
	Board* pBoard;     
	char figure;         
	Direction dir; 
	int color; 
	bool isColored; 
	bool isSilented;

	//This function changes the direction of the ghost
	virtual void turnAround() = 0;

	//This function returns true if the ghost can't move, and false otherwise
	virtual bool isStuck() const = 0;

public:

	//C'tor
	Ghost(Board* _pBoard, char _figure, Direction _dir, int _color, bool _isColored = false, bool _isSilented = false) : pBoard(_pBoard), figure(_figure), dir(_dir), color(_color), isColored(_isColored), isSilented(_isSilented) {}

	//Virtual D'tor
	virtual ~Ghost() {};

	//This function is initializing the ghost according to the received x and y values
	void init(int x, int y);

	//This function returns the figure of the ghost
	char getFigure() const { return figure; }

	//This function sets new direction for the ghost
	void setDirection(Direction newDir) { dir = newDir; }

	//This function returns the direction of the ghost
	Direction getDirection() const { return dir; }

	//This function moves the ghost according to the direction if possible and returns indication accordingly
	virtual int move();

	//This function returns the ghost point
	const Point& getGhostPoint() const { return body; }

	//This function deletes the ghost from the board and from the screen
	void remove() const;


};

