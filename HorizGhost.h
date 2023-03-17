#pragma once
#include "Ghost.h"

class HorizGhost : public Ghost
{
	//This function changes the direction of the ghost
	void turnAround() override { (getDirection() == Direction::Right) ? setDirection(Direction::Left) : setDirection(Direction::Right); }

	//This function returns true if the ghost can't move, and false otherwise
	bool isStuck() const override { return (getGhostPoint().getNextChar(Direction::Right) != Figures::Empty && getGhostPoint().getNextChar(Direction::Left) != Figures::Empty); }

public:

	//C'tor
	using Ghost::Ghost;
};

