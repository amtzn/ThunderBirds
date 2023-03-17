#include "Ghost.h"

void Ghost::init(int x, int y)
{
	body.setX(x);
	body.setY(y);
	body.setBoard(pBoard);
}

int Ghost::move() 
{
	char nextCh = body.getNextChar(dir);
	if (nextCh == Figures::Empty) {
		body.move(dir, figure, color, isColored, isSilented);
		return MoveStatus::Moved;
	}
	else if (nextCh == Figures::BigShip || nextCh == Figures::SmallShip) {
		return MoveStatus::HitShip;
	}
	else if (isStuck()) {
		return MoveStatus::CantMove;
	}
	else {
		turnAround();
		return move();
	}
}

void Ghost::remove() const
{
	pBoard->set(body.getX(), body.getY(), Figures::Empty);
	body.del();
}
