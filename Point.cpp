#include "Point.h"

void Point::move(Direction dir, char ch, int color, bool isColored, bool isSilented) {
	pBoard->set(x, y, Figures::Empty);
	del();
	switch (dir) {
	case Direction::Up:
		--y;
		break;
	case Direction::Down:
		++y;
		break;
	case Direction::Left:
		--x;
		break;
	case Direction::Right:
		++x;
		break;
	}
	if (!isSilented) {
		draw(ch, color, isColored);
	}
	pBoard->set(x, y, ch);
}

char Point::getNextChar(Direction dir) const{
	switch (dir) {
	case Direction::Up:
		return(pBoard->get(x, y - 1));
		break;
	case Direction::Down:
		return(pBoard->get(x, y + 1));
		break;
	case Direction::Left:
		return(pBoard->get(x - 1, y));
		break;
	case Direction::Right:
		return(pBoard->get(x + 1, y));
		break;
	default:
		break;
	}
}

Point Point::getNextPoint(Direction dir) const
{
	switch (dir) {
	case Direction::Up:
		return Point(getX(), getY() - 1);
		break;
	case Direction::Left:
		return Point(getX() - 1, getY());
		break;
	case Direction::Right:
		return Point(getX() + 1, getY());
		break;
	case Direction::Down:
		return Point(getX(), getY() + 1);
		break;
	default:
		break;
	}
}

void Point::draw(char ch, int color, bool isColored) const {
	gotoxy(x, y);
	if (isColored) {
		setTextColor(color);
		std::cout << ch;
		setTextColor(Color::WHITE);
	}
	else {
		std::cout << ch;
	}

}

bool Point::operator==(const Point& point) const
{
	return (x == point.x && y == point.y);
}