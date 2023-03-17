#pragma once
#include "Ghost.h"

class VertGhost : public Ghost
{
	//This function changes the direction of the ghost
	void turnAround() override { (getDirection() == Direction::Up) ? setDirection(Direction::Down) : setDirection(Direction::Up); }

	//This function returns true if the ghost can't move, and false otherwise
	bool isStuck() const override {	return (getGhostPoint().getNextChar(Direction::Up) != Figures::Empty && getGhostPoint().getNextChar(Direction::Down) != Figures::Empty); }

public:

	//C'tor
	using Ghost::Ghost;

};

