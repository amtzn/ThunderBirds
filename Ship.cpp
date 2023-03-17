#include "Ship.h"

Ship::Ship(Board* _pBoard, char _type, char _figure, int _color, bool _isColored, bool _isSilented) :pBoard(_pBoard), type(_type), figure(_figure), dir(Direction::Stat), color(_color), isColored(_isColored), isSilented(_isSilented) {
	if (type == Keys::Big) {
		size = shipSize::Big;
		maxWeight = 6;
	}
	else {
		size = shipSize::Small;
		maxWeight = 2;
	}
}

void Ship::init(int x, int y) {
	int i = 0;
	while (body[i].getX() != initValue) 
		i++;
	body[i] = Point(x, y, pBoard);
}

int Ship::move() {
	char next1, next2;
	switch (dir) {
	case Direction::Up:
		next1 = body[0].getNextChar(dir);
		next2 = body[1].getNextChar(dir);
		if (next1 == Figures::Empty && next2 == Figures::Empty) {
			for (int i = 0; i < size; i++) {
				body[i].move(dir, figure, color, isColored, isSilented);
			}
			return MoveStatus::Moved;
		}
		else if (next1 == Figures::WinPoint || next2 == Figures::WinPoint) {
			return MoveStatus::HitEndPoint;
		}
		else if (!isNextMoveValid()) {
			return MoveStatus::CantMove;
		}
		else if (isGhost(next1) || isGhost(next2)) {
			return MoveStatus::HitGhost;
		}
		else if (next1 >= '0' && next1 <= '9' || next2 >= '0' && next2 <= '9'){
			return MoveStatus::HitBlock;
		}
		else{
			return MoveStatus::CantMove;
		}
		break;
	case Direction::Down:
		next1 = body[size - 1].getNextChar(dir);
		next2 = body[size - 2].getNextChar(dir);
		if (next1 == Figures::Empty && next2 == Figures::Empty) {
			for (int i = size - 1; i >= 0; i--) {
				body[i].move(dir, figure, color, isColored, isSilented);
			}
			return MoveStatus::Moved;
		}
		else if (next1 == Figures::WinPoint || next2 == Figures::WinPoint) {
			return MoveStatus::HitEndPoint;
		}
		else if (isGhost(next1) || isGhost(next2)) {
			return MoveStatus::HitGhost;
		}
		else {
			return MoveStatus::CantMove;
		}
		break;
	case Direction::Left:
		next1 = body[0].getNextChar(dir);
		next2 = body[size - 2].getNextChar(dir);
		if (next1 == Figures::Empty && next2 == Figures::Empty) {
			for (int i = 0; i < size; i++) {
				body[i].move(dir, figure, color, isColored, isSilented);
			}
			return MoveStatus::Moved;
		}
		else if (next1 == Figures::WinPoint || next2 == Figures::WinPoint) {
			return MoveStatus::HitEndPoint;
		}
		else if (!isNextMoveValid()) {
			return MoveStatus::CantMove;
		}
		else if (isGhost(next1) || isGhost(next2)) {
			return MoveStatus::HitGhost;
		}
		else if (next1 >= '0' && next1 <= '9' || next2 >= '0' && next2 <= '9') {
			return MoveStatus::HitBlock;
		}
		else {
			return MoveStatus::CantMove;
		}
		break;
	case Direction::Right:
		next1 = body[1].getNextChar(dir);
		next2 = body[size - 1].getNextChar(dir);
		if (next1 == Figures::Empty && next2 == Figures::Empty) {
			for (int i = size - 1; i >= 0; i--) {
				body[i].move(dir, figure, color, isColored, isSilented);
			}
			return MoveStatus::Moved;
		}
		else if (next1 == Figures::WinPoint || next2 == Figures::WinPoint) {
			return MoveStatus::HitEndPoint;
		}
		else if (!isNextMoveValid()) {
			return MoveStatus::CantMove;
		}
		else if (isGhost(next1) || isGhost(next2)) {
			return MoveStatus::HitGhost;
		}
		else if (next1 >= '0' && next1 <= '9' || next2 >= '0' && next2 <= '9') {
			return MoveStatus::HitBlock;
		}
		else {
			return MoveStatus::CantMove;
		}
		break;
	case Direction::Stat:
		return MoveStatus::CantMove;
	default:
		break;
	}
}

bool Ship::isNextMoveValid() const
{
	switch (type) {
	case Keys::Big:
		for (int i = 0; i < size; i++) {
			if (body[i].getNextChar(dir) == Figures::Wall || body[i].getNextChar(dir) == Figures::SmallShip) {
				return false;
			}
		}
		return true;
	case Keys::Small:
		for (int i = 0; i < size; i++) {
			if (body[i].getNextChar(dir) == Figures::Wall || body[i].getNextChar(dir) == Figures::BigShip) {
				return false;
			}
		}
		return true;
	default:
		return false;
	}
}

bool Ship::isGhost(char ch) const
{
	return (ch == Figures::VertGhost || ch == Figures::HorizGhost || ch == Figures::WanderGhost);
}

Point Ship::getNextPoint(Direction dir) const
{
	switch (dir) {
	case Direction::Up:
	case Direction::Left:
		return body[0].getNextPoint(dir);
		break;
	case Direction::Right:
		return body[1].getNextPoint(dir);
		break;
	}
}

void Ship::remove() const
{
	for (int i = 0; i < size; i++) {
		pBoard->set(body[i].getX(), body[i].getY(), Figures::Empty);
		body[i].del();
	}
}
