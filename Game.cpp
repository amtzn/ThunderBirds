#include "Game.h"

void Game::start () const
{
	srand(246);
	char choice = UserChoice::Init;
	hide_cursor();
	menu.printEnteryScreen();    

	while (choice != UserChoice::Exit) {
		menu.printMenu();
		choice = _getch();

		switch (choice) {
		case UserChoice::ColorFullGame:
			runFullGame(true);
			break;
		case UserChoice::NoneColorFullGame:
			runFullGame(false);
			break;
		case UserChoice::ColorSingleGame:
			runSingleGame(true);
			break;
		case UserChoice::NoneColorSingleGame:
			runSingleGame(false);
			break;
		case UserChoice::KeysAndInst:
			menu.printKeysAndInst();
			while (choice != Keys::ESC)
				choice = _getch();
		default:
			break;
		}
	}
	menu.printExit();  
}


void Game::startLoadedGame() const
{
	Board boards[FullGameLength];
	Point infoPlaces[FullGameLength];
	int timeLefts[FullGameLength];
	int lives = 3;
	GameStatus gameStatus = GameStatus::Initial;
	std::string ScreenFilesNames[FullGameLength];
	std::string stepsFilesNames[FullGameLength];

	if (!getAndCheckGameFiles(ScreenFilesNames)) {
		return;
	}

	for (int i = 0; i < FullGameLength; i++) {
		std::fstream boardFile(ScreenFilesNames[i], std::ios_base::in);
		initGameInfo(boardFile, boards[i], infoPlaces[i], timeLefts[i]);
		boardFile.close();

		if (!isValidGameBoard(boards[i])) {
			return;
		}
	}

	if (!getAndCheckFilesBySuffix(ScreenFilesNames, stepsFilesNames, "steps")) {
		return;
	}
	
	for (int i = 0; i < 3 && lives > 0; i++) {
		std::fstream Sfile(stepsFilesNames[i], std::ios_base::in);  // The file validation happens in the getAndCheckFilesBySuffix Function . here we assume the file is ok
		while (lives > 0 && gameStatus != GameStatus::Exit) {
			gameStatus = GameRound(lives, boards[i], infoPlaces[i], timeLefts[i]).runLoadedFile(Sfile);
			if (gameStatus == GameStatus::Win) {
				break;
			}
			lives--;
		}
		Sfile.close();
	}

	printEndGameMassage(gameStatus, lives);
}

void Game::startSilentGame() const
{
	Board boards[FullGameLength];
	Point infoPlaces[FullGameLength];
	int timeLefts[FullGameLength];
	int lives = 3;
	bool testStatus = true;
	std::string ScreenFilesNames[FullGameLength];
	std::string stepsFilesNames[FullGameLength];
	std::string resultsFilesNames[FullGameLength];

	if (!getAndCheckGameFiles(ScreenFilesNames)) {
		return;
	}

	for (int i = 0; i < FullGameLength; i++) {
		std::fstream boardFile(ScreenFilesNames[i], std::ios_base::in);
		initGameInfo(boardFile, boards[i], infoPlaces[i], timeLefts[i]);
		boardFile.close();

		if (!isValidGameBoard(boards[i])) {
			return;
		}
	}

	if (!getAndCheckFilesBySuffix(ScreenFilesNames, stepsFilesNames, "steps")) {
		return;
	}

	if (!getAndCheckFilesBySuffix(ScreenFilesNames, resultsFilesNames, "result")) {
		return;
	}

	for (int i = 0; i < FullGameLength; i++) {
		std::fstream Sfile(stepsFilesNames[i], std::ios_base::in); // The file validation happens in the getAndCheckFilesBySuffix Function . here we assume the file is ok
		std::fstream Rfile(resultsFilesNames[i], std::ios_base::in); // The file validation happens in the getAndCheckFilesBySuffix Function . here we assume the file is ok

		int timeRes;
		int gameRes;
		Rfile >> timeRes;
		while (testStatus && !Rfile.eof()) {
			Rfile >> gameRes;
			testStatus = GameRound(lives, boards[i], infoPlaces[i], timeLefts[i], false, true).runSilentFile(Sfile, timeRes, gameRes);
			if (testStatus == false) {
				break; 
			}
			Rfile >> timeRes;
		}
		Sfile.close();
		Rfile.close();
	}

	if (testStatus) {
		std::cout << "Test Passed =)\n";
	}
	else {
		std::cout << "Test Failed =(\n";
	}
}


void Game::runFullGame(bool isColored) const {

	Board boards [FullGameLength];
	Point infoPlaces [FullGameLength];
	int timeLefts[FullGameLength];
	int lives = 3;
	GameStatus gameStatus = GameStatus::Initial;
	std::string filesNames[FullGameLength];

	if (!getAndCheckGameFiles(filesNames)) {
		return;
	}

	for (int i = 0; i < FullGameLength; i++) {
		std::fstream boardFile(filesNames[i], std::ios_base::in);
		initGameInfo(boardFile, boards[i], infoPlaces[i], timeLefts[i]);
		boardFile.close();

		if (!isValidGameBoard(boards[i])) {
			return;
		}
	}

	for (int i = 0; i < FullGameLength && lives > 0; i++) {
		runGameRound(lives, gameStatus, filesNames[i], boards[i], infoPlaces[i], timeLefts[i], isColored);
	}

	printEndGameMassage(gameStatus, lives);
}

void Game::runSingleGame(bool isColored) const
{
	Board board;
	Point infoPlace;
	int timeLeft;
	std::string fileName;
	int lives = 3;
	GameStatus gameStatus = GameStatus::Initial;
	clrscr();

	if(!getAndCheckUserFile(fileName)) {
		return;
	}

	std::fstream boardFile(fileName, std::ios_base::in);
	initGameInfo(boardFile, board, infoPlace, timeLeft);
	boardFile.close();

	if (!isValidGameBoard(board)) {
		return;
	}

	runGameRound(lives, gameStatus, fileName, board, infoPlace, timeLeft, isColored);
	printEndGameMassage(gameStatus, lives);
}

void Game::runGameRound(int& lives, GameStatus& gameStatus, std::string fileName, Board& board, Point& infoPlace, int timeLeft, bool isColored) const
{
	std::fstream* recordFileP = nullptr;
	std::fstream* resultFileP = nullptr;
	if (mode == GameMode::Record && !openAndCheckRecordFiles(recordFileP, resultFileP, fileName)) {
		return;
	}

	while (lives > 0 && gameStatus != GameStatus::Exit) {
		gameStatus = GameRound(lives, board, infoPlace, timeLeft, isColored).run(recordFileP, resultFileP);
		if (gameStatus == GameStatus::Win) {
			break;
		}
		lives--;
	}
	if (recordFileP) {
		recordFileP->close();
		delete recordFileP;
	}
	if (resultFileP) {
		resultFileP->close();
		delete resultFileP;
	}

}

void Game::printEndGameMassage(GameStatus gameStatus, int lives) const
{
	if (gameStatus != GameStatus::Exit) {
		if (lives > 0) {
			printWinMessage();
		}
		else {
			printLoseMessege();
		}
	}
}

void Game::printLoseMessege() const 
{
	clrscr();
	std::cout << "                                                                               " << std::endl <<
		"                           /&@@&(              (&&&#.                          " << std::endl <<
		"                      @@@@@@@@@@@@@&     @@@@@@@@@@@@@@@@@                     " << std::endl <<
		"                   @@@@@*        @@@@   @@@@     ,.    #@@@@%                  " << std::endl <<
		"                 *@@@&            @@@@   &@@@       .@@@  @@@@                 " << std::endl <<
		"                ,@@@               *@@@/   @@@@        *@% *@@@                " << std::endl <<
		"                @@@&          (@@@@@@@@@    @@@@        .@, @@@@               " << std::endl <<
		"                @@@#          @@@@         @@@@@@        @* @@@@               " << std::endl <<
		"                #@@@           ,@@@%   (@@@@@&              @@@.               " << std::endl <<
		"                 @@@@            @@@@  @@@@               .@@@#                " << std::endl <<
		"                  /@@@@           @@@@ @@@@              @@@@.                 " << std::endl <<
		"                    @@@@@          .@@@@@@@            @@@@%                   " << std::endl <<
		"                      %@@@@          @@@@@@         /@@@@*                     " << std::endl <<
		"                         @@@@@        %@@@@       @@@@@                        " << std::endl <<
		"                           ,@@@@@       *.    ,@@@@@                           " << std::endl <<
		"                              .@@@@@(      %@@@@@                              " << std::endl <<
		"                                  @@@@@@@@@@@@                                 " << std::endl <<
		"                                     ,@@@@                                     " << std::endl <<
		"               _____                         ____                              " << std::endl <<
		"              / ____|                       / __ \\                             " << std::endl <<
		"             | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __              " << std::endl <<
		"             | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|             " << std::endl <<
		"             | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |                " << std::endl <<
		"              \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|                " << std::endl <<
		"                                                                               ";
	Sleep(3000);
}

void Game::printWinMessage() const
{
	clrscr();
	std::cout << "                                                                               " << std::endl <<
		"                          @@@@@@@@@@@@@@@@@@@@@@@@@@@@                         " << std::endl <<
		"                    @@@@@@@@&                      @@@@@@@@/                   " << std::endl <<
		"                  @@@(    @@@          &.          @@@    @@@*                 " << std::endl <<
		"                  @@@     /@@          @@         (@@      @@@                 " << std::endl <<
		"                  @@@      @@@       @@@@@@       @@@      @@/                 " << std::endl <<
		"                   @@@      @@@      @@@@@@      @@@      @@@                  " << std::endl <<
		"                    @@@.     @@@           ,    @@@     #@@@                   " << std::endl <<
		"                      @@@@    @@@             %@@@    @@@@                     " << std::endl <<
		"                        &@@@@@, @@@%        @@@@  @@@@@(                       " << std::endl <<
		"                             @@@@@@@@@@@@@@@@@@@@@@                            " << std::endl <<
		"                                      *@@                                      " << std::endl <<
		"                                   #@@@@@@@@,                                  " << std::endl <<
		"                              ,@@@@@%      @@@@@@                              " << std::endl <<
		"                              *@@             #@@                              " << std::endl <<
		"                            @@@@@@@@@@@@@@@@@@@@@@@@                           " << std::endl <<
		"                            @@@                  @@@                           " << std::endl <<
		"                            @@@@@@@@@@@@@@@@@@@@@@@@                           " << std::endl <<
		"                                 _                                             " << std::endl <<
		"                                (_)                                            " << std::endl <<
		"                       __      ___ _ __  _ __   ___ _ __                       " << std::endl <<
		"                       \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__|                      " << std::endl <<
		"                        \\ V  V /| | | | | | | |  __/ |                         " << std::endl <<
		"                         \\_/\\_/ |_|_| |_|_| |_|\\___|_|                         " << std::endl <<
		"                                                                               ";

	Sleep(3000);
}

bool Game::isFileOk(std::string fileName) const
{
	std::fstream currFile(fileName, std::ios_base::in);
	bool res = currFile.is_open();
	currFile.close();

	return res;
}

bool Game::isGameFilesOk(std::string filesNames[], int size) const
{
	for (int i = 0; i < size; i++) {
		if (!isFileOk(filesNames[i])) {
			fileErrorMsg("ERROR OPENING GAME FILE, PLEASE CHECK AND TRY AGAIN...", 8, 12);
			return false;
		}
	}
	return true;
}

bool Game::getAndCheckUserFile(std::string& fileName) const
{
	printGetFileMassage();
	std::cin >> fileName;
	if (!isFileOk(fileName)) {
		fileErrorMsg("ERROR OPENING GAME FILE, PLEASE CHECK AND TRY AGAIN...", 13, 12);
		return false;
	}

	return true;
}

bool Game::getAndCheckGameFiles(std::string filesNames[]) const
{
	makeBoardNamesFile();
	std::fstream resultFile("result.txt", std::ios_base::in);
	int i = 0;
	while (i < 3 && std::getline(resultFile, filesNames[i])) {
		i++;
	}

	resultFile.close();

	if (i < 3) {
		fileErrorMsg("THERE ARE NO AT LEAST 3 GAME FILES, PLEASE CHECK AND TRY AGAIN...", 7, 12);
		return false;
	}

	if (!(isGameFilesOk(filesNames, 3))) {
		return false;
	}

	return true;
}

bool Game::getAndCheckFilesBySuffix(std::string screenFilesNames[], std::string filesNames[], std::string suffix) const
{
	for (int i = 0; i < FullGameLength; i++) {
		filesNames[i] = screenFilesNames[i].substr(0, screenFilesNames[i].length() - 6);
		filesNames[i].append(suffix);
		if (!isFileOk(filesNames[i])) {
			if (!suffix.compare("steps")) {
				fileErrorMsg("ERROR OPENING STEPS FILE, PLEASE CHECK AND TRY AGAIN...", 8, 12);
			}
			else {
				fileErrorMsg("ERROR OPENING RESULT FILE, PLEASE CHECK AND TRY AGAIN...", 8, 12);
			}
			return false;
		}
	}

	return true;
}

bool Game::openAndCheckRecordFiles(std::fstream*& recordFileP, std::fstream*& resultFileP, std::string fileName) const {
	std::string recordFile = fileName.substr(0, fileName.length() - 6);
	recordFile.append("steps");
	std::string resultFile = fileName.substr(0, fileName.length() - 6);
	resultFile.append("result");
	recordFileP = new std::fstream(recordFile, std::ios_base::out);
	resultFileP = new std::fstream(resultFile, std::ios_base::out);
	if (!recordFileP->is_open() || !resultFileP->is_open()) {
		if (recordFileP->is_open()) {
			resultFileP->close();
		}
		else {
			recordFileP->close();
		}
		fileErrorMsg("ERROR OPENING FILE, PLEASE CHECK AND TRY AGAIN...", 18, 12);
		return false;
	}
	return true;
}

void Game::printGetFileMassage() const
{
	gotoxy(12, 10);
	std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
	gotoxy(12, 11);
	std::cout << "W                                                      W";
	gotoxy(12, 12);
	std::cout << "W     Please Enter File Name:                          W";
	gotoxy(12, 13);
	std::cout << "W                                                      W";
	gotoxy(12, 14);
	std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
	gotoxy(42, 12);
}

void Game::initGameInfo(std::fstream& boardFile, Board& board, Point& infoPlace, int& timeLeft) const
{
	std::string garbage;
	boardFile >> timeLeft;
	std::getline(boardFile, garbage);
	for (int i = 0; i < ScreenSize::Width; i++) {
		for (int j = 0; j < ScreenSize::Height - 1; j++) {
			board.set(j, i, boardFile.get());
			if (board.get(j, i) == Figures::LegendInfo) {
				infoPlace.setX(j);
				infoPlace.setY(i);
				board.set(j, i, Figures::Empty);
			}
		}
		board.set(ScreenSize::Height - 1, i, '\0');
		std::getline(boardFile, garbage);
	}
}

void Game::fileErrorMsg(std::string errorMsg, int col, int row) const
{
	clrscr();
	gotoxy(col, row);
	std::cout << errorMsg << "\n";
	Sleep(3000);
	clrscr();
}

bool Game::isValidGameBoard(Board& board) const
{
	bool isBigShipExist = false;
	bool isSmallShipExist = false;
	bool isEndingPointExist = false;
	Point BigShip[shipSize::Big];
	Point SmallShip[shipSize::Small];

	for (int i = 0; i < ScreenSize::Width; i++) {
		for (int j = 0; j < ScreenSize::Height - 1; j++) {
			Point currP(j, i);
			char currCh = board.get(j, i);
			if (currCh == Figures::BigShip) {
				if (!isBigShipExist && (i < (ScreenSize::Width - 1)) && (j < (ScreenSize::Height - 2))) {
					if (board.get(j + 1, i) == Figures::BigShip && board.get(j, i + 1) == Figures::BigShip && board.get(j + 1, i + 1) == Figures::BigShip) {
						BigShip[0].setX(j); BigShip[0].setY(i);
						BigShip[1].setX(j); BigShip[1].setY(i + 1);
						BigShip[2].setX(j + 1); BigShip[2].setY(i);
						BigShip[3].setX(j + 1); BigShip[3].setY(i + 1);
						isBigShipExist = true;
					}
					else {
						fileErrorMsg("Board is not valid! Shape of Big Ship isn't right" ,0,0);
						return false;
					}
				}
				else if (isBigShipExist) {
					bool found = false;
					for (int k = 0; k < shipSize::Big; k++) {
						if (currP == BigShip[k]) {
							found = true;
						}
					}
					if (!found) {
						fileErrorMsg("Board is not valid! Too many Big Ship characters", 0, 0);
						return false;
					}
				}
				else {
					fileErrorMsg("Board is not valid! Big Ship in the last row or column", 0, 0);
					return false;
				}
			}
			else if (currCh == Figures::SmallShip) {
				if (!isSmallShipExist && (j < (ScreenSize::Height - 2))) {
					if (board.get(j + 1, i) == Figures::SmallShip) {
						SmallShip[0].setX(j); SmallShip[0].setY(i);
						SmallShip[1].setX(j + 1); SmallShip[1].setY(i);
						isSmallShipExist = true;
					}
					else {
						fileErrorMsg("Board is not valid! Shape of Small Ship isn't right", 0, 0);
						return false;
					}
				}
				else if (isSmallShipExist) {
					bool found = false;
					for (int k = 0; k < shipSize::Small; k++) {
						if (currP == SmallShip[k]) {
							found = true;
						}
					}
					if (!found) {
						fileErrorMsg("Board is not valid! Too many Small Ship characters", 0, 0);
						return false;
					}
				}
				else {
					fileErrorMsg("Board is not valid! Small Ship in the last column", 0, 0);
					return false;
				}
			}
			else if (currCh == Figures::WinPoint) {
				isEndingPointExist = true;
			}
			else if (currCh >= '0' && currCh <= '9') {
				continue;
			}
			else if (currCh != Figures::Empty && currCh != Figures::HorizGhost && currCh != Figures::VertGhost && currCh != Figures::WanderGhost && currCh != Figures::Wall) {
				fileErrorMsg("Board is not valid! Invalid character in the board", 0, 0);
				return false;
			}
		}
	}
	if (!isEndingPointExist) {
		fileErrorMsg("Board is not valid! Ending Point does not exist", 0, 0);
		return false;
	}
	if (!isBigShipExist) {
		fileErrorMsg("Board is not valid! Big Ship does not exist", 0, 0);
		return false;
	}
	if (!isSmallShipExist) {
		fileErrorMsg("Board is not valid! Small Ship does not exist", 0, 0);
		return false;
	}
	return true;
}





