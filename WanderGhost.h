#pragma once
#include <cstdlib>
#include "Ghost.h"

enum class WanderType{Random, ByDir};

class WanderGhost : public Ghost
{
	int counter = 1;
	WanderType type; 

	//This function changes the direction of the ghost
	void turnAround() override {
		 setDirection((Direction)(rand() % 4));
	}

	//This function returns true if the ghost can't move, and false otherwise
	bool isStuck() const override {
		return (getGhostPoint().getNextChar(Direction::Up) != Figures::Empty &&
			getGhostPoint().getNextChar(Direction::Down) != Figures::Empty &&
			getGhostPoint().getNextChar(Direction::Right) != Figures::Empty && 
			getGhostPoint().getNextChar(Direction::Left) != Figures::Empty);
	}

public:

	//C'tor
	WanderGhost(Board* _pBoard, char _figure, Direction _dir, int _color, bool _isColored = false, bool _isSilented = false, WanderType _type = WanderType::Random) : Ghost(_pBoard, _figure, _dir, _color, _isColored, _isSilented), type(_type) {};

	//This function moves the ghost according to the direction and ghost type if possible and returns indication accordingly
	int move() override;
};