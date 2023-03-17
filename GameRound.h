#pragma once

#include "MovingObjManager.h"
#include <string>
#include <conio.h>
#include <fstream>

enum class GameStatus{Exit, Win, OutOfTime, OverWeight, HitGhost, Running, Initial};

class GameRound
{
	GameStatus isRunning;
	int timeLeft;
	int shipsStatus[2];  //shipsStatus[0] = Small, shipsStatus[1] = Big  
	int lives;
	char actShip;
	Board board;
	MovingObjManager movObj;
	bool isColored;
	bool isSilented;
	Point infoPlace;

	//This function reveives a character and operates accordingly (switch active ship/change active ship/etc.)
	void handleHitByKey(char key);

	//This function receives the result of the current move and returns the round status accordingly 
	GameStatus gameRoundStatus(int movRes);

	//This function prints the pause game massage
	void printPauseMessage() const;

	//This function prints matching end round massage
	void printEndRoundMessage() const;

	//This function prints the out of time massage
	void printOutOfTimeMessage() const;

	//This function prints the overweight massage
	void printOverWeightMassage() const;

	//This function prints the hit ghost massage
	void printHitGhostMassage() const;

	//This function handles the pause game, receives the choice from the user and returns indication accordingly
	GameStatus handlePauseGame();

	//This function prints the active ship on the screen
	void printActiveShip() const;

	//This function prints the player remain steps on the screen
	void printTime() const;

	//This function prints the player remian lives on the screen
	void printLives() const;

	//This function prints the player round info (lives, steps and active ship) on the screen
	void printRoundInfo() const;

public:

	//C'tor
	GameRound(int _lives, Board _board, Point& _infoPlace, int _timeLeft, bool _isColored = false, bool _isSilented = false);

	//This function runs a game round/lap
	GameStatus run(std::fstream* recordFileP, std::fstream* resultFileP);

	//This function runs a loaded game round/lap
	GameStatus runLoadedFile(std::fstream& Sfile);	

	//This function runs a silent loaded game round/lap
	bool runSilentFile(std::fstream& Sfile, int timeRes, int gameRes);

};

