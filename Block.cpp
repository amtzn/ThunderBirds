#include "Block.h"

void Block::init(int x, int y)
{
	if (pBoard->get(x, y) != figure) {
		return;
	}

	for (int i = 0; i < size; i++) {
		if (x == body[i].getX() && y == body[i].getY()) {
			return;
		}
	}

	body.push_back(Point(x, y, pBoard));
	size++;

	//rec calls
	init(x + 1, y);  // right
	init(x, y + 1);  //down
	init(x - 1, y);  // left
	init(x, y - 1);  //up
}

void Block::move(Direction dir)
{
	for (int i = 0; i < size; i++) {
		switch (dir) {
		case Direction::Up:
			body[i].setY(body[i].getY() - 1);
			break;
		case Direction::Down:
			body[i].setY(body[i].getY() + 1);
			break;
		case Direction::Left:
			body[i].setX(body[i].getX() - 1);
			break;
		case Direction::Right:
			body[i].setX(body[i].getX() + 1);
			break;
		}
	}
}

char Block::canFall() const
{
	char res = Figures::Empty;
	for (int i = 0; i < size; i++) {
		Point nextPoint(body[i].getX(), body[i].getY() + 1);
		char currCh = body[i].getNextChar(Direction::Down);
		if (currCh == Figures::VertGhost || currCh == Figures::HorizGhost || currCh == Figures::WanderGhost) {
			res = Figures::VertGhost;
		}
		else if(currCh != Figures::Empty && !isPointInBlock(nextPoint)) {
			return Figures::Wall;
		}
	}
	return res;
}

bool Block::isPointInBlock(const Point& point) const
{
	for (int i = 0; i < size; i++) {
		if (body[i] == point) {
			return true;
		}
	}
	return false;
}

void Block::draw() const
{
	for (int i = 0; i < size; i++) {
		pBoard->set(body[i].getX(), body[i].getY(), figure);
		if (!isSilented) {
			body[i].draw(figure, color, isColored);
		}
	}
}

void Block::remove() const
{
	for (int i = 0; i < size; i++) {
		pBoard->set(body[i].getX(), body[i].getY(), Figures::Empty);
		body[i].del();
	}
}







