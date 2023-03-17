#include "MovingObjManager.h"

MovingObjManager::~MovingObjManager()
{
	for (int i = 0; i < ghosts.size(); i++) {
		delete ghosts[i];
	}
}

void MovingObjManager::init(GameMode gameMode)
{
	for (int row = 0; row < ScreenSize::Width; row++) {
		for (int col = 0; col < ScreenSize::Height; col++) {
			if (pBoard->get(col, row) == bShip.getFigure()) {
					bShip.init(col, row);
			}
			else if (pBoard->get(col, row) == sShip.getFigure()) {
					sShip.init(col, row);
			}
			else if (pBoard->get(col, row) == Figures::HorizGhost) {
				HorizGhost* ghost = new HorizGhost(pBoard, Figures::HorizGhost, Direction::Right, Color::GREY, isColored, isSilented);
				ghost->init(col, row);
				ghosts.push_back(ghost);
			}
			else if (pBoard->get(col, row) == Figures::VertGhost) {
				VertGhost* ghost = new VertGhost(pBoard, Figures::VertGhost, Direction::Up, Color::GREY, isColored, isSilented);
				ghost->init(col, row);
				ghosts.push_back(ghost);
			}
			else if (pBoard->get(col, row) == Figures::WanderGhost) {
				WanderGhost* ghost;
				if (gameMode != GameMode::Loaded) {
					ghost = new WanderGhost(pBoard, Figures::WanderGhost, (Direction)(rand() % 4), Color::GREY, isColored, isSilented);
				}
				else {
					ghost = new WanderGhost(pBoard, Figures::WanderGhost, Direction::Stat, Color::GREY, isColored, isSilented, WanderType::ByDir);
				}
				ghost->init(col, row);
				ghosts.push_back(ghost);
			}
			else if (pBoard->get(col, row) >= '0' && pBoard->get(col, row) <='9') {
				if (!isBlockPoint(Point(col, row))) {
					Block block(pBoard, pBoard->get(col, row), Color::LIGHTMAGENTA, isColored, isSilented);
					block.init(col, row);
					blocks.push_back(block);
				}
			}
		}
	}
}

void MovingObjManager::setActive(char key) 
{
	switch (key) {
	case Keys::Big:
		actShipP = &bShip;
		break;
	case Keys::Small:
		actShipP = &sShip;
		break;
	}

	bShip.setDirection(Direction::Stat);
	sShip.setDirection(Direction::Stat);
}

void MovingObjManager::setDirection(char newDir)
{
	Direction dir;
	switch (newDir) {
	case Keys::Up:
		actShipP->setDirection(Direction::Up);
		break;
	case Keys::Down:
		actShipP->setDirection(Direction::Down);
		break;
	case Keys::Left:
		actShipP->setDirection(Direction::Left);
		break;
	case Keys::Right:
		actShipP->setDirection(Direction::Right);
		break;
	default:
		break;
	}
	
}

bool MovingObjManager::isBlockPoint(const Point& point) const
{
	for (const auto& block: blocks) {
		if (block.isPointInBlock(point)) {
			return true;
		}
	}
	return false;
}

bool MovingObjManager::isPointInBlocksChain(std::vector<Block*>& blocksChain, const Point& point) const
{
	for (int i = 0; i < blocksChain.size(); i++) {
		if ((blocksChain[i])->isPointInBlock(point)) {
			return true;
		}
	}
	return false;
}

int MovingObjManager::getBlockIndex(const Point& point) const
{
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].isPointInBlock(point)) {
			return i;
		}
	}
	return initValue;
}

void MovingObjManager::removeShip()
{
	actShipP->remove();
}

void MovingObjManager::moveBlocksDown()
{
	for (auto& block : blocks) {
		char res = block.canFall();
		if(res == Figures::Empty) {
			block.remove();
			block.move(Direction::Down);
			block.draw();
		}
		if (res == Figures::VertGhost) {
			for (int i = 0; i < block.getSize(); i++) {
				Point downPoint = block.getBlockPoint(i).getNextPoint(Direction::Down);
				char downCh = pBoard->get(downPoint.getX(), downPoint.getY());
				if (downCh == Figures::VertGhost || downCh == Figures::HorizGhost || downCh == Figures::WanderGhost) {
					killGhost(downPoint);
				}
			}
		}
	}
}

void MovingObjManager::killGhost(const Point& point)
{
	for (int i = 0; i < ghosts.size(); i++) {
		if (ghosts[i]->getGhostPoint() == point) {
			ghosts[i]->remove();
			std::vector<Ghost*>::iterator it;
			it = ghosts.begin() + i;
			delete ghosts[i];
			ghosts.erase(it);
		}
	}
}

int MovingObjManager::moveShips()
{
	int movRes;
	movRes = actShipP->move();
	if (movRes == MoveStatus::HitBlock) {
		if (pushBlocks(actShipP->getNextPoint(actShipP->getDirection()), actShipP->getDirection())) {
			actShipP->move();
			movRes = MoveStatus::Moved;
		}
		else
			movRes = MoveStatus::CantMove;
	}
	else if (movRes == MoveStatus::Moved) {
		std::vector<Block*>blocksChain;
		carryBlocks(blocksChain);
		pushBlocksChain(blocksChain, actShipP->getDirection());
	}

	return movRes;
}

int MovingObjManager::moveGhosts(std::string steps)
{
	int movRes;
	int index = 2;
	for (int i = 0; i < ghosts.size(); i++) {
		if (ghosts[i]->getFigure() == Figures::WanderGhost && !steps.empty()) {
			int dir = steps[index] - '0';
			ghosts[i]->setDirection((Direction)dir);
			index++;
		}
		movRes = ghosts[i]->move();
		if (movRes == MoveStatus::HitShip) {
			return MoveStatus::HitShip;
		}
	}
	return MoveStatus::Moved;
}

bool MovingObjManager::pushBlocks(Point nextPoint, Direction dir)
{
	std::vector<Block*>blocksChain; 
	int totalSize = 0;
	bool canPush = false;

	canPush = buildBlocksChainRec(blocksChain, totalSize, dir, nextPoint);
	if (canPush) {
		switch (dir) {
		case Direction::Up:
			nextPoint.setX(nextPoint.getX() + 1);
			canPush = buildBlocksChainRec(blocksChain, totalSize, dir, nextPoint);
			break;
		case Direction::Right:
		case Direction::Left:
			if (actShipP->getType() == Keys::Big) {
				nextPoint.setY(nextPoint.getY() + 1);
				canPush = buildBlocksChainRec(blocksChain, totalSize, dir, nextPoint);
			}
			break;
		default:
			break;
		}
	}
	
	if (canPush) {
		carryBlocks(blocksChain);
		pushBlocksChain(blocksChain, dir);
		return true;
	}
	else {
		return false;
	}
}

bool MovingObjManager::buildBlocksChainRec(std::vector<Block*>& blocksChain, int& totalSize, Direction dir, Point nextPoint)
{
	char currChar = pBoard->get(nextPoint.getX(), nextPoint.getY());
	bool res = true;

	if (currChar == Figures::Empty) {
		return true;
	}

	if (!(currChar >= '0' && currChar <= '9')) {
		return false;
	}

	if (isPointInBlocksChain(blocksChain, nextPoint)) {
		return true;
	}

	int index = getBlockIndex(nextPoint);

	blocksChain.push_back(&(blocks[index]));
	totalSize += blocks[index].getSize();

	if (actShipP->getMaxWeight() < totalSize) {
		return false;
	}
	
	//Rec calls
    for (int i = 0; i < blocks[index].getSize() && res; i++) {
		res = res && buildBlocksChainRec(blocksChain, totalSize, dir, blocks[index].getBlockPoint(i).getNextPoint(dir));
	}
	
	return res;
}

void MovingObjManager::pushBlocksChain(std::vector<Block*>& blocksChain, Direction dir)
{
	for (int i = 0; i < blocksChain.size(); i++) {
		blocksChain[i]->remove();
	}

	for (int i = 0; i < blocksChain.size(); i++) {
		blocksChain[i]->move(dir);
	}
	for (int i = 0; i < blocksChain.size(); i++) {
		blocksChain[i]->draw();
	}

}

bool MovingObjManager::isValidWeight(Ship* shipP)
{
	//False = OverWeight, True = Valid Weight
	std::vector<Block*>blocksChain;
	int totalSize = 0;
	bool res = true;       
	Point currPoint;

	currPoint = shipP->getNextPoint(Direction::Up);

	res = checkWeight(blocksChain, totalSize, Direction::Up, currPoint, shipP);

	if (res) {
		currPoint.setX(currPoint.getX() + 1);
		res = checkWeight(blocksChain, totalSize, Direction::Up, currPoint, shipP);
	}

	return res;
}

bool MovingObjManager::isShipsOverWeight()
{
	return !(isValidWeight(&sShip) && isValidWeight(&bShip));
}

std::string MovingObjManager::getSteps() const
{
	std::string steps;
	steps.push_back(actShipP->getType());
	char ch;
	switch (actShipP->getDirection()) {
	case Direction::Up:
		ch = Keys::Up;
		break;
	case Direction::Down:
		ch = Keys::Down;
		break;
	case Direction::Left:
		ch = Keys::Left;
		break;
	case Direction::Right:
		ch = Keys::Right;
		break;
	case Direction::Stat:
		ch = Keys::Stat;
		break;
	default: 
		break;
	}
	steps.push_back(ch);
	for (auto& ghost : ghosts) {
		if (ghost->getFigure() == Figures::WanderGhost) {
			steps.push_back((int)ghost->getDirection() + '0');
		}
	}
	return steps;
}

bool MovingObjManager::checkWeight(std::vector<Block*>& blocksChain, int& totalSize, Direction dir, Point nextPoint, Ship* shipP)
{
	//True = Weight is ok, False = Over Weight
	bool res = true;
	char currChar = pBoard->get(nextPoint.getX(), nextPoint.getY());

	if (!(currChar >= '0' && currChar <= '9')) {   // Not block
		return true;
	}

	if (isPointInBlocksChain(blocksChain, nextPoint)) {
		return true;
	}

	int index = getBlockIndex(nextPoint);

	if (overWeightExtraCheck(blocksChain, index, shipP)) {
		return true;
	}
	
	blocksChain.push_back(&(blocks[index]));
	totalSize += blocks[index].getSize();

	if (shipP->getMaxWeight() < totalSize){
			return false;
	}

	for (int i = 0; i < blocks[index].getSize() && res; i++) {
		res = res && checkWeight(blocksChain, totalSize, dir, blocks[index].getBlockPoint(i).getNextPoint(dir), shipP);
	}

	return res;
}

bool MovingObjManager::overWeightExtraCheck(std::vector<Block*>& blocksChain, int index, Ship* shipP) const
{
	for (int i = 0; i < blocks[index].getSize(); i++) {
		Point downPoint(blocks[index].getBlockPoint(i).getNextPoint(Direction::Down));
		char downChar = blocks[index].getBlockPoint(i).getNextChar(Direction::Down);
		if (!(blocks[index].isPointInBlock(downPoint))) {
			if (blocksChain.size() == 0) {
				if (downChar != Figures::Empty && downChar != shipP->getFigure()){
					return true;
				}
			}

			bool isIn = false;

			for (int j = 0; j < blocksChain.size() && !isIn; j++) {
				if (blocksChain[j]->isPointInBlock(downPoint)) {
					isIn = true;
				}
			}

			if (!isIn) {
				if (downChar != Figures::Empty && downChar != shipP->getFigure()){
					return true;
				}
			}
		}
	}

	return false;
}

void MovingObjManager::carryBlocks(std::vector<Block*>& blocksChain)
{
	Point p = actShipP->getNextPoint(Direction::Up);
	Direction dir = actShipP->getDirection();

	if (dir == Direction::Left) {
		p.setX(p.getX() + 1);
		carryBlocksRec(blocksChain, dir, p);
		p.setX(p.getX() + 1);
	}
	else if (dir == Direction::Right) {
		p.setX(p.getX() + 1);
		carryBlocksRec(blocksChain, dir, p);
		p.setX(p.getX() - 1);
	}
	else {
		return;
	}

	if (!isPointInBlocksChain(blocksChain, p)) {
		carryBlocksRec(blocksChain, dir, p);
	}
}

void MovingObjManager::carryBlocksRec(std::vector<Block*>& blocksChain, Direction dir, Point nextPoint)
{
	char currChar = pBoard->get(nextPoint.getX(), nextPoint.getY());
	bool ispushed = false;

	if (!(currChar >= '0' && currChar <= '9')) {      //Not Block
		return;
	}

	int index = getBlockIndex(nextPoint);

	char res = isBlockCanMove(blocks[index], dir, blocksChain);

	if (res == Figures::Wall) {
		return;
	}

	else {
		if (res == Figures::Empty && !isPointInBlocksChain(blocksChain, blocks[index].getBlockPoint(0))) {
			blocksChain.push_back(&(blocks[index]));
			ispushed = true;
		}
		for (int i = 0; i < blocks[index].getSize() && res; i++) {
			Point p = blocks[index].getBlockPoint(i).getNextPoint(Direction::Up);
			if (!isPointInBlocksChain(blocksChain, p) && !blocks[index].isPointInBlock(p)) {
				carryBlocksRec(blocksChain, dir, p);
			}
		}
	}

	res = isBlockCanMove(blocks[index], dir, blocksChain);

	if (res == Figures::Empty && !ispushed && !isPointInBlocksChain(blocksChain, blocks[index].getBlockPoint(0))) {
		blocksChain.push_back(&(blocks[index]));
	}
}

char MovingObjManager::isBlockCanMove(const Block& block, Direction dir, std::vector<Block*>& blocksChain) const
{
	char res = Figures::Empty;

	for (int i = 0; i < block.getSize(); i++) {
		Point nextPoint = block.getBlockPoint(i);
		switch (dir) {
		case Direction::Right:
			nextPoint.setX(nextPoint.getX() + 1);
			break;
		case Direction::Left:
			nextPoint.setX(nextPoint.getX() - 1);
			break;
		}
		if (!block.isPointInBlock(nextPoint) && !isPointInBlocksChain(blocksChain, nextPoint)) {
			if (block.getBlockPoint(i).getNextChar(dir) >= '0' && block.getBlockPoint(i).getNextChar(dir) <= '9') {
				res = Figures::Block;
			}
			else if (block.getBlockPoint(i).getNextChar(dir) != Figures::Empty) {
				return Figures::Wall;
			}
		}
	}
	return res;
}
