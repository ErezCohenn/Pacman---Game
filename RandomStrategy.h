#pragma once
#include "Strategy.h"
#include "point.h"
#include "Creature.h"
#include "board.h"
#include "ghost.h"

class RandomStrategy : virtual public Strategy
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	unsigned int countSteps;
	int amountSameDir; // The amount of steps in the same direction

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	RandomStrategy(int amount) : amountSameDir(amount), countSteps(0) {}

	virtual void strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman = { -1,-1 }) override;
	
	//--------------------------------------Get Functions------------------------------------------------//
	int getAmountSameDir() const { return amountSameDir; }
	unsigned int getCountSteps() const { return countSteps; }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setAmountSameDir(int amount) { amountSameDir = amount; }
	void setCountSteps(int count) { countSteps = count; }
	
};