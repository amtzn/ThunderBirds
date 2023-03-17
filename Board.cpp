#include "Board.h"

void Board::printBoard(bool isColored) const{
	for (int i = 0; i < ScreenSize::Width; i++) {
		for (int j = 0; j < ScreenSize::Height; j++) {
			if (isColored) {
				setRightColor(board[i][j]);
			}
			if (board[i][j] == Figures::Wall) {
				std::cout << Figures::pWall;
			}
			else {
				std::cout << board[i][j];
			}
		}
		if (i < ScreenSize::Width - 1) {
			std::cout << std::endl;
		}
	}
}

void Board::setRightColor(char ch) const
{
	if (ch == Figures::BigShip) {
		setTextColor(Color::LIGHTGREEN);
	}
	else if (ch == Figures::SmallShip) {
		setTextColor(Color::LIGHTBLUE);
	}
	else if (ch == Figures::WinPoint) {
		setTextColor(Color::LIGHTCYAN);
	}
	else if (ch == Figures::Wall) {
		setTextColor(Color::YELLOW);
	}
	else if (ch == Figures::VertGhost || ch == Figures::HorizGhost || ch == Figures::WanderGhost) {
		setTextColor(Color::GREY);
	}
	else if (ch >= '0' && ch <= '9') {
		setTextColor(Color::LIGHTMAGENTA);
	}
	else {
		setTextColor(Color::WHITE);
	}
}
