#pragma once
#include "SmartStrategy.h"
#include "RandomStrategy.h"
#include "point.h"
#include "Creature.h"
#include "board.h"
#include "ghost.h"

class MediocreStrategy : public SmartStrategy, RandomStrategy
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	int amountSameSmartDir;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	MediocreStrategy(int amount) : RandomStrategy(amount), amountSameSmartDir(15 + rand() % 11){}

	virtual void strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman = { -1,-1 }) override;
	virtual void setCountSteps(int count) override
	{
		RandomStrategy::setCountSteps(count);
		SmartStrategy::setCountSteps(count);
	}
};