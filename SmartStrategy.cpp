#include "SmartStrategy.h"
//-----------------------------------------------------------------------------------------------//
void SmartStrategy::strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman)
{
	priority_queue<Distance> priority_dist; // priority disttance from the ghosts to the pacman
	vector<vector<bool>> visit(board.getRowNumber()); // Declare the visitited
	vector<Point> attackPacman;

	initVisit(board, visit, true);

	Point adjacent_pacman;
	int countDist;

	for (unsigned int indexCreature = 0; indexCreature < ghosts.size(); indexCreature++) // calculate the distance from creatures[i] to pacman
	{
		initVisit(board , visit , false); // initialize visitited array to false

		adjacent_pacman = BFS_Move(board, ghosts[indexCreature].getCurr(), p_packman , visit, countDist);

		Distance dist(countDist, indexCreature, adjacent_pacman);
		priority_dist.push(dist);

	}

	while (!priority_dist.empty())
	{
		initVisit(board , visit, false);

		for (unsigned int i = 0; i < attackPacman.size(); i++)
		{
			visit[attackPacman[i].get_Y()][attackPacman[i].get_X()] = true;
		}

		Distance dist = priority_dist.top();
		priority_dist.pop();
		attackPacman.push_back(dist.getPoint());

		Point nextStep = BFS_Move(board, p_packman, ghosts[dist.getIndexGhost()].getCurr(), visit, countDist);

		if (nextStep == ghosts[dist.getIndexGhost()].getCurr())
		{
			initVisit(board, visit, false);
			nextStep = BFS_Move(board, p_packman, ghosts[dist.getIndexGhost()].getCurr(), visit, countDist);
		}

		ghosts[dist.getIndexGhost()].move(nextStep);
		countSteps++;
	}
		
	
}
//-----------------------------------------------------------------------------------------------//
Point SmartStrategy::BFS_Move(const Board& board, const Point& start, const Point& end, vector<vector<bool>>& visit, int& count)
{
	Point adjacent_cell, cell;
	// Stores indices of the matrix cells
	queue<queueNode> q;

	// Mark the starting cell as visitited and push it into the queue
	queueNode adjacent_node;
	queueNode first = { start, 0 };
	q.push(first);


	// Iterate while the queue is not empty
	while (!q.empty())
	{
		queueNode curr = q.front();
		Point cell = curr.pt;
		
		q.pop();

		// Go to the adjacent cells
		for (int i = 0; i < 4; i++)
		{
			adjacent_cell = cell + Creature::directions[i];

			if (adjacent_cell == end)
			{
				count = curr.dist + 1;
				return cell; // return the next move for the ghost
			}

			else if (board.isValidMove(adjacent_cell) && visit[adjacent_cell.get_Y()][adjacent_cell.get_X()] == false) // If cell not visited yet and valid move
			{
				adjacent_node = { adjacent_cell , curr.dist + 1 };
				q.push(adjacent_node);
				visit[adjacent_cell.get_Y()][adjacent_cell.get_X()] = true;
				
			}
		}
	}

	count = 0;
	return end;
}
//-----------------------------------------------------------------------------------------------//
void SmartStrategy::initVisit(const Board& board, vector<vector<bool>>& visit, bool start)
{
	if (start) // initialize visit 
	{
		for (unsigned int row = 0; row < board.getRowNumber(); row++)
		{
			for (unsigned int col = 0; col < board.getLineLen(); col++)
			{
				visit[row].push_back(false);
			}
		}
	}
	
	else
	{
		for (unsigned int row = 0; row < board.getRowNumber(); row++)
		{
			for (unsigned int col = 0; col < board.getLineLen(); col++)
			{
				visit[row][col] = false;
			}
		}
	}

	
}
//-----------------------------------------------------------------------------------------------//