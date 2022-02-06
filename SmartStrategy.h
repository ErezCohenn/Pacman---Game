#pragma once
#include "Strategy.h"
#include "point.h"
#include "board.h"
#include "ghost.h"
#include "Creature.h"
#include <queue>
#include <vector>
#include <array>
#include "Distance.h"

using std::array;
using std::priority_queue;
using std::queue;
using std::vector;

class SmartStrategy : virtual public Strategy
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	unsigned int countSteps;

	//-----------------------------------Private Member Functions----------------------------------------//
	void initVisit(const Board& board, vector<vector<bool>>& visit, bool start);
	Point BFS_Move(const Board& board, const Point& start, const Point& end, vector<vector<bool>>& visit, int& count);

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	SmartStrategy() : countSteps(0) {}
	virtual void strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman = { -1,-1 }) override;

	//--------------------------------------Get Functions------------------------------------------------//
	unsigned int getCountSteps() const { return countSteps; }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setCountSteps(int count) { countSteps = count; }
};

// queue node for bfs algoirthm
struct queueNode
{
	Point pt;  // The coordinates of a cell
	int dist = 0;  // cell's distance of from the source
};