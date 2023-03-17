#pragma once

#include "Menu.h"
#include "GameRound.h"

struct UserChoice {
	constexpr static int ColorFullGame = '1';
	constexpr static int NoneColorFullGame = '2';
	constexpr static int ColorSingleGame = '3';
	constexpr static int NoneColorSingleGame = '4';
	constexpr static int KeysAndInst = '8';
	constexpr static int Exit = '9';
	constexpr static int Init = '0';
};

class Game
{
	Menu menu;
	GameMode mode;

	//This function runs a colord/not colored full game according to the bool value
	void runFullGame(bool isColored) const;

	//This function runs a colord/not colored single game according to the bool value 
	void runSingleGame(bool isColored) const;

	//This function runs a game round according to the received file name
	void runGameRound(int& lives, GameStatus& gameStatus, std::string fileName, Board& board, Point& infoPlace, int timeLeft, bool isColored) const;
	 
	//This function prints the end game massage according to the game status (win/lose)
	void printEndGameMassage(GameStatus gameStatus, int lives) const;

	//This function prints the interface for the file name input
	void printGetFileMassage() const;

	//This function prints winning masssage
	void printWinMessage() const;

	//This function prints a lose game message
	void printLoseMessege() const;

	//This funtion returns true if the file opened successfully, and false otherwise 
	bool isFileOk(std::string fileName) const;

	//This funtion returns true if all the game files opened successfully, and false otherwise 
	bool isGameFilesOk(std::string filesNames[], int size) const;

	//This function receives file name from the user and returns true if the file is exists and opened successfully, and false otherwise 
	bool getAndCheckUserFile(std::string& fileName) const;

	//This function checks if there is at least 3 game files, if yes it checks if the files is ok and returns true. false otherwise
	bool getAndCheckGameFiles(std::string filesNames[]) const;

	//This function checks if there is at least 3 files with the received suffix , if yes it checks if the files is ok and returns true. false otherwise
	bool getAndCheckFilesBySuffix(std::string screenFilesNames[], std::string filesNames[], std::string suffix) const;

	//This function checks if the record and result files exist, if yes it checks if the files is ok and returns true. false otherwise
	bool openAndCheckRecordFiles(std::fstream*& recordFileP, std::fstream*& resultFileP, std::string fileName) const;

	//This function return true if the game board is valid, false otherwise
	bool isValidGameBoard(Board& board) const;

	//This function inits the game board and the game round info parameters 
	void initGameInfo(std::fstream& boardFile, Board& board, Point& infoPlace, int& timeLeft) const;

	//This function prints error message according to string, row and column
	void fileErrorMsg(std::string errorMsg, int col, int row) const;

public:     

	//C'tor
	Game(GameMode _mode) : mode(_mode) {};

	//This function starts the game and operates the menus logic
	void start() const;

	//This function starts the loaded game
	void startLoadedGame() const;

	//This function starts the silented game
	void startSilentGame() const;
};

