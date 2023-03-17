#pragma once

#include "Block.h"
#include "Ship.h"
#include "VertGhost.h"
#include "HorizGhost.h"
#include "WanderGhost.h"
#include <cctype>

class MovingObjManager
{
	Ship bShip;
	Ship sShip;
	std::vector<Ghost*> ghosts;
	std::vector<Block> blocks;
	Board* pBoard;
	Ship* actShipP;
	bool isColored;
	bool isSilented;

	//This function returns true if the blocks have been pushed according to the received direction, and false otherwise
	bool pushBlocks(Point nextPoint, Direction dir);

	//This function returns true if the received point is in one of the blocks, and false otherwise
	bool isBlockPoint(const Point& point) const;

	//This function returns true if the received point is in one of the blocks in the blocks chain, and false otherwise
	bool isPointInBlocksChain(std::vector<Block*>& blocksChain, const Point& point) const;

	//this function returns the index of the block according to the received point. 
	int getBlockIndex(const Point& point) const;

	//This function removes the ghost from the ghosts vector according to the received point
	void killGhost(const Point& point);

	/*This function adds to the blocks chain vector all the adjacent blocks according to the received direction 
	   and returns true if the blocks chain can be pushed by the ship, and false otherwise */
	bool buildBlocksChainRec(std::vector<Block*>& blocksChain, int& totalSize, Direction dir, Point nextPoint);

	//This function pushes the blocks in the blocks chain according to the received direction 
	void pushBlocksChain(std::vector<Block*>& blocksChain, Direction dir);

	//This function returns true if the blocks weight on the ship is vaild, and false otherwise
	bool isValidWeight(Ship* shipP);

	//This function calculates the blocks weight on the ship recursively and returns true if the weight is valid 
	bool checkWeight(std::vector<Block*>& blocksChain, int& totalSize, Direction dir, Point nextPoint, Ship* shipP);

	//This function checks if the block in the index that received needs to be added to the blocks chain 
	bool overWeightExtraCheck(std::vector<Block*>& blocksChain, int index, Ship* shipP) const;

	//This function receives blocks chain vector and appends the blocks that need to be carried
	void carryBlocks(std::vector<Block*>& blocksChain);

	//This function is the carryBlocks recursive helper function
	void carryBlocksRec(std::vector<Block*>& blocksChain, Direction dir, Point nextPoint);

	//This function checks if the received block can be moved according to the direction and returns indication
	char isBlockCanMove(const Block& block, Direction dir, std::vector<Block*>& blocksChain) const;

public:

 	//C'tor
	MovingObjManager(Board* _pBoard, bool _isColored, bool _isSilented) : bShip(_pBoard, Keys::Big, Figures::BigShip, Color::LIGHTGREEN, _isColored, _isSilented), sShip(_pBoard, Keys::Small, Figures::SmallShip, Color::LIGHTBLUE, _isColored, _isSilented),
		pBoard(_pBoard), actShipP(&bShip), isColored(_isColored), isSilented(_isSilented){}

	//D'tor
	~MovingObjManager();

	//This function initializing the ships and blocks by calling the object init function according to the current character from the board
	void init(GameMode gameMode = GameMode::Standard);

	//This function sets the active ship 
	void setActive(char key);

	//This function sets new direction to the active ship
	void setDirection(char newDir);

	//This function moves the ship and pushes the block if needed according to the ship direction and returns indication 
	int moveShips();

	//This function moves the blocks down and kill ghosts if needed 
	void moveBlocksDown();

	//This function removes the active ship from the board and screen
	void removeShip();

	//This function moves the ghosts and returns indication 
	int moveGhosts(std::string steps = "");

	//This function returns true if at least one of the ships is in over weight
	bool isShipsOverWeight();

	//This function returns a string that represents the moving objects steps in one iteration
	std::string getSteps() const;

	//This function returns the active ship type
	char getActive() const { return actShipP->getType(); }
};


