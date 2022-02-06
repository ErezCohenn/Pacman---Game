#pragma once
#include "board.h"
#include "point.h"
#include "ghost.h"


class Strategy
{
public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	virtual void strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman = { -1,-1 })= 0;
	virtual void setCountSteps(int count) = 0;

	virtual ~Strategy() {};
};