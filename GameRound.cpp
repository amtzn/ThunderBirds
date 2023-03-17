#include "GameRound.h"

GameRound::GameRound(int _lives, Board _board, Point& _infoPlace, int _timeLeft, bool _isColored, bool _isSilented) :
	isRunning(GameStatus::Running), shipsStatus{ ShipStatus::InGame, ShipStatus::InGame }, lives(_lives), board(_board), infoPlace(_infoPlace), timeLeft(_timeLeft),
	actShip(Keys::Big), movObj(&board, _isColored, _isSilented), isColored(_isColored), isSilented(_isSilented) {}


GameStatus GameRound::run(std::fstream* recordFileP, std::fstream* resultFileP)
{
	clrscr();
	movObj.init();
	char key = Keys::Stat;
	bool gameStarted = false;
	board.printBoard(isColored);
	printRoundInfo();

	while (isRunning == GameStatus::Running) {
		if (_kbhit()) {
			key = _getch();
			key = std::tolower(key);
			handleHitByKey(key);
			if (!gameStarted) {
				if (key == Keys::Up || key == Keys::Down || key == Keys::Right || key == Keys::Left) {
					gameStarted = true;
				}
			}
		}
		if (isRunning == GameStatus::Running) {
			if (gameStarted) {
				timeLeft--;
				printTime();
			}
			if (movObj.isShipsOverWeight()) {
				isRunning = GameStatus::OverWeight;
			}
			else {
				int res = movObj.moveShips();
				int ghostRes = movObj.moveGhosts();
				if (recordFileP) {
					*recordFileP << movObj.getSteps() << '\n';
				}
				movObj.moveBlocksDown();
				if (ghostRes == MoveStatus::HitShip) {
					isRunning = GameStatus::HitGhost;
				}
				else {
					isRunning = gameRoundStatus(res);
				}
			}
		}
		Sleep(120);   
	}
	printEndRoundMessage();

	if (resultFileP) {
		*resultFileP << timeLeft << " " << ((isRunning == GameStatus::Win) ? (int)isRunning : 0) << '\n' ;
	}

	return isRunning;
}

GameStatus GameRound::runLoadedFile(std::fstream& Sfile)
{
	movObj.init(GameMode::Loaded);
	hide_cursor();
	clrscr();
	std::string currSteps;
	board.printBoard(false);
	printRoundInfo();
	bool gameStarted = false;

	while (isRunning == GameStatus::Running) 
	{
		std::getline(Sfile, currSteps);
		if (currSteps.size() == 0) {
			clrscr();
			std::cout << "ERROR READING RECORD FILE\n";
			isRunning = GameStatus::Exit;
			break;
		}
		if (currSteps[1] != Keys::Stat) {
			gameStarted = true;
		}
		if (gameStarted) {
			timeLeft--;
			printTime();
		}
		actShip = currSteps[0];
		if (currSteps[0] == Keys::Big) {
			movObj.setActive(Keys::Big);
		}
		else {
			movObj.setActive(Keys::Small);
		}
		printActiveShip();
		movObj.setDirection(currSteps[1]);

		if (isRunning == GameStatus::Running) {
			if (movObj.isShipsOverWeight()) {
				isRunning = GameStatus::OverWeight;
			}
			else {
				isRunning = gameRoundStatus(movObj.moveShips());
				movObj.moveBlocksDown();
				if (movObj.moveGhosts(currSteps) == MoveStatus::HitShip) {
					isRunning = GameStatus::HitGhost;
				}
			}
		}
		Sleep(30);
	}
	printEndRoundMessage();
	return isRunning;
}

bool GameRound::runSilentFile(std::fstream& Sfile, int timeRes, int gameRes)
{
	movObj.init(GameMode::Loaded);
	hide_cursor();
	std::string currSteps;
	bool gameStarted = false;

	while (isRunning == GameStatus::Running) {
		std::getline(Sfile, currSteps);
		if (currSteps.size() == 0) {
			isRunning = GameStatus::Exit;
			break;
		}
		if (currSteps[1] != Keys::Stat) {
			gameStarted = true;
		}
		if (gameStarted) {
			timeLeft--;
		}
		actShip = currSteps[0];
		if (currSteps[0] == Keys::Big) {
			movObj.setActive(Keys::Big);
		}
		else {
			movObj.setActive(Keys::Small);
		}
		movObj.setDirection(currSteps[1]);

		if (isRunning == GameStatus::Running) {
			if (movObj.isShipsOverWeight()) {
				isRunning = GameStatus::OverWeight;
			}
			else {
				isRunning = gameRoundStatus(movObj.moveShips());
				movObj.moveBlocksDown();
				if (movObj.moveGhosts(currSteps) == MoveStatus::HitShip) {
					isRunning = GameStatus::HitGhost;
				}
			}
		}
	}
	clrscr();
	if (timeRes == timeLeft) {
		if (isRunning == GameStatus::Win && (GameStatus)gameRes == GameStatus::Win) {
			return true;
		}
		else if (isRunning != GameStatus::Win && (GameStatus)gameRes != GameStatus::Win){
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void GameRound::handleHitByKey(char key)
{
	switch (key) {
	case Keys::Big:
		if (shipsStatus[1] == ShipStatus::NotInGame)
			key = Keys::Small;
	case Keys::Small:
		if (shipsStatus[0] == ShipStatus::NotInGame)
			key = Keys::Big;
		actShip = key;
		movObj.setActive(key);
		printActiveShip();
		break;
	case Keys::ESC:
		isRunning = handlePauseGame();
		break;
	case Keys::Up:
	case Keys::Down:
	case Keys::Left:
	case Keys::Right:
		movObj.setDirection(key);
		break;
	default:
		break;
	}
}

GameStatus GameRound::gameRoundStatus(int movRes)
{
	if (movRes == MoveStatus::HitEndPoint) {
		switch (actShip)
		{
		case Keys::Big:
			shipsStatus[1] = ShipStatus::NotInGame;
			actShip = Keys::Small;
			movObj.setDirection(Keys::Stat);
			movObj.removeShip();
			movObj.setActive(Keys::Small);
			break;
		case Keys::Small:
			shipsStatus[0] = ShipStatus::NotInGame;
			actShip = Keys::Big;
			movObj.setDirection(Keys::Stat);
			movObj.removeShip();
			movObj.setActive(Keys::Big);
			break;
		default:
			break;
		}

		if (shipsStatus[0] != shipsStatus[1] && !isSilented) {
			printActiveShip();
		}
	}

	if (shipsStatus[0] == ShipStatus::NotInGame && shipsStatus[1] == ShipStatus::NotInGame) {
		return GameStatus::Win;
	}

	if (movRes == MoveStatus::HitGhost) {
		return GameStatus::HitGhost;
	}
	if (timeLeft == 0) {
		return GameStatus::OutOfTime;
	}

	return GameStatus::Running;
}

void GameRound::printEndRoundMessage() const
{
	switch (isRunning) {
	case GameStatus::OutOfTime:
		printOutOfTimeMessage();
		break;
	case GameStatus::OverWeight:
		printOverWeightMassage();
		break;
	case GameStatus::HitGhost:
		printHitGhostMassage();
		break;
	default:
		break;
	}
}

GameStatus GameRound::handlePauseGame()
{
	char choice;
	movObj.setDirection(Keys::Stat);
	printPauseMessage();
	choice = _getch();
	while (choice != '9' && choice != Keys::ESC) {
		choice = _getch();
	}

	if (choice == Keys::ESC) {
		clrscr();
		board.printBoard(isColored);
		printRoundInfo();
		return GameStatus::Running;

	}
	else {
		return GameStatus::Exit;
	}
}

void GameRound::printActiveShip() const
{
	gotoxy(infoPlace.getX() + 9, infoPlace.getY() + 2);
	if (actShip == Keys::Big) {
		std::cout << "BIG  ";
	}
	else {
		std::cout << "SMALL";
	}
}

void GameRound::printTime() const
{
	gotoxy(infoPlace.getX() + 7, infoPlace.getY() + 1);
	std::cout << timeLeft << "  ";
}

void GameRound::printLives() const
{
	gotoxy(infoPlace.getX() + 8, infoPlace.getY());
	if (isColored) {
		setTextColor(Color::LIGHTRED);
	}

	switch (lives) {
	case 1:
		std::cout << Figures::Heart;
		break;
	case 2:
		std::cout << Figures::Heart << " " << Figures::Heart;
		break;
	case 3:
		std::cout << Figures::Heart << " " << Figures::Heart << " " << Figures::Heart;
		break;
	default:
		break;
	}

	if (isColored) {
		setTextColor(Color::WHITE);
	}
}

void GameRound::printRoundInfo() const
{
	gotoxy(infoPlace.getX() + 1, infoPlace.getY());
	std::cout << "LIVES: ";
	gotoxy(infoPlace.getX() + 1, infoPlace.getY() + 1);
	std::cout << "TIME: ";
	gotoxy(infoPlace.getX() + 1, infoPlace.getY() + 2);
	std::cout << "ACTIVE: ";

	printActiveShip();
	printTime();
	printLives();
}

void GameRound::printPauseMessage() const
{
	clrscr();
	std::cout << "                                                                               " << std::endl <<
		"                                                                               " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                               @@@@@@@    @@@@@@@                              " << std::endl <<
		"                                                                               " << std::endl <<
		"                        _____                         _                        " << std::endl <<
		"                       |  __ \\                       | |                       " << std::endl <<
		"                       | |__) |_ _ _   _ ___  ___  __| |                       " << std::endl <<
		"                       |  ___/ _` | | | / __|/ _ \\/ _` |                       " << std::endl <<
		"                       | |  | (_| | |_| \\__ \\  __/ (_| |                       " << std::endl <<
		"                       |_|   \\__,_|\\__,_|___/\\___|\\__,_|                       " << std::endl <<
		"                                                                               " << std::endl <<
		"                    PRESS ESC AGAIN TO CONTINUE OR 9 TO EXIT                   " << std::endl <<
		"                                                                               ";
}

void GameRound::printOutOfTimeMessage() const
{
	clrscr();
	std::cout << "                                                                               " << std::endl <<
		"                                  . %@@@@@@&                                   " << std::endl <<
		"                                   @@@@@@@@@@                                  " << std::endl <<
		"                                     @@@@@@       @,                           " << std::endl <<
		"                               . %@@@@@@@@@@@@& @@@@@@                         " << std::endl <<
		"                             @@@@@@@@@@@@@@@@@@@@@@@@                          " << std::endl <<
		"                          *@@@@@@@            #@@@@@@&                         " << std::endl <<
		"                         @@@@@%                  ,@@@@@.                       " << std::endl <<
		"                       .@@@@@/@@@@                 @@@@@&                      " << std::endl <<
		"                       @@@@@   .&@@@@@#             &@@@@                      " << std::endl <<
		"                       @@@@.       #@@@@@@@          @@@@#                     " << std::endl <<
		"                       @@@@,         #@@@@@          @@@@(                     " << std::endl <<
		"                       @@@@@                        @@@@@                      " << std::endl <<
		"                        @@@@@.                     @@@@@                       " << std::endl <<
		"                         @@@@@@,                 @@@@@@                        " << std::endl <<
		"                           @@@@@@@@,        .@@@@@@@@                          " << std::endl <<
		"                              @@@@@@@@@@@@@@@@@@@@                             " << std::endl <<
		"                                   ,@@@@@@@@/                                  " << std::endl <<
		"                          _            __   _   _                              " << std::endl <<
		"                         | |          / _| | | (_)                             " << std::endl <<
		"               ___  _   _| |_    ___ | |_  | |_ _ _ __ ___   ___               " << std::endl <<
		"              / _ \\| | | | __|  / _ \\|  _| | __| | '_ ` _ \\ / _ \\              " << std::endl <<
		"             | (_) | |_| | |_  | (_) | |   | |_| | | | | | |  __/              " << std::endl <<
		"              \\___/ \\__,_|\\__|  \\___/|_|    \\__|_|_| |_| |_|\\___|              " << std::endl <<
		"                                                                               ";

	Sleep(1500);
}

void GameRound::printOverWeightMassage() const
{
	clrscr();
	std::cout << "                                                                                " << std::endl <<
		"                                    %@@@@@@@/                                   " << std::endl <<
		"                                  @@@@@(*%@@@@&                                 " << std::endl <<
		"                                 @@@&       @@@&                                " << std::endl <<
		"                                 @@@@       @@@#                                " << std::endl <<
		"                                  @@@@@@&@@@@@(                                 " << std::endl <<
		"                             &@@@@@@@@@@@@@@@@@@@@@/                            " << std::endl <<
		"                            &@@@@@@@@@@@@@@@@@@@@@@@/                           " << std::endl <<
		"                           /@@@@@@@@@@@@@@@@@@@@@@@@@                           " << std::endl <<
		"                           @@@@@@@@@@@@@@@@@@@@@@@@@@@                          " << std::endl <<
		"                          @@@@@@@@@@@@@@@@@@@@@@@@@@@@,                         " << std::endl <<
		"                         *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                         " << std::endl <<
		"                         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&                        " << std::endl <<
		"                        &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*                       " << std::endl <<
		"                       *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       " << std::endl <<
		"                        %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*                       " << std::endl <<
		"                                                                                " << std::endl <<
		"             ____                  __          __  _       _     _              " << std::endl <<
		"            / __ \\                 \\ \\        / / (_)     | |   | |             " << std::endl <<
		"           | |  | |_   _____ _ __   \\ \\  /\\  / /__ _  __ _| |__ | |_            " << std::endl <<
		"           | |  | \\ \\ / / _ \\ '__|   \\ \\/  \\/ / _ \\ |/ _` | '_ \\| __|           " << std::endl <<
		"           | |__| |\\ V /  __/ |       \\  /\\  /  __/ | (_| | | | | |_            " << std::endl <<
		"            \\____/  \\_/ \\___|_|        \\/  \\/ \\___|_|\\__, |_| |_|\\__|           " << std::endl <<
		"                                                      __/ |                     " << std::endl <<
		"                                                     |___/                      ";
	Sleep(1500);
}

void GameRound::printHitGhostMassage() const
{
	clrscr();
	std::cout << "                                                                                " << std::endl <<
		"                                      /%%*                                      " << std::endl <<
		"                               &&&&&&&&&&&&&&&&&&                               " << std::endl <<
		"                            &&&&&&&&&&&&&&&&&&&&&&&&                            " << std::endl <<
		"                         ,&&&&&&&&&&&&&&&&&&&&&&&&&&&&                          " << std::endl <<
		"                        &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                        " << std::endl <<
		"                       &&&&&&&      &&&&&&&&      &&&&&&&                       " << std::endl <<
		"                       &&&&&&&      &&&&&&&&      &&&&&&&                       " << std::endl <<
		"                      &&&&&&&&&&#%&&&&&&&&&&&&%%&&&&&&&&&                       " << std::endl <<
		"                      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                       " << std::endl <<
		"                      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                       " << std::endl <<
		"                      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                       " << std::endl <<
		"                      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                       " << std::endl <<
		"                      &&&&&&&&( &&&&&&&&&&&&&&&& %&&&&&&&                       " << std::endl <<
		"                      &&&&.         &&&&&&&&         *&&&                       " << std::endl <<
		"                                                                                " << std::endl <<
		"    _    _ _ _          _   _                      _____ _               _      " << std::endl <<
		"   | |  (_) | |        | | | |                    / ____| |             | |     " << std::endl <<
		"   | | ___| | | ___  __| | | |__  _   _    __ _  | |  __| |__   ___  ___| |_    " << std::endl <<
		"   | |/ / | | |/ _ \\/ _` | | '_ \\| | | |  / _` | | | |_ | '_ \\ / _ \\/ __| __|   " << std::endl <<
		"   |   <| | | |  __/ (_| | | |_) | |_| | | (_| | | |__| | | | | (_) \\__ \\ |_    " << std::endl <<
		"   |_|\\_\\_|_|_|\\___|\\__,_| |_.__/ \\__, |  \\__,_|  \\_____|_| |_|\\___/|___/\\__|   " << std::endl <<
		"                                   __/ |                                        " << std::endl <<
		"                                  |___/                                         " << std::endl <<
		"                                                                                ";
	Sleep(1500);
}