#pragma once
#include <time.h>
#include<iostream>
#include "board.h"
#include "ghost.h"

using std::cout;

class Fruit : public Creature
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	int length, waitCounter, waitRand, stepsCounter;
	bool erase = false, start = true, appearOnBoard = false;
	
	//-----------------------------------Private Member Functions-----------------------------------------//


public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	Fruit(Colors _color = Colors::LIGHTGREEN, int _x = -1, int _y = -1):
	Creature(_color, (5 + rand() % 5) + '0', _x, _y)
	{
		length = waitCounter = stepsCounter = waitRand = 0;
	}
		
	void init(char value, const Point& initP);
	void move(const Board& board, const Point& nextStep);
	void eraseFromBoard();
	
	
	//--------------------------------------Get Functions-----------------------------------------------//
	bool getStart() const { return start; }
	bool getIserased() const { return erase; }
	bool isAppearOnBoard() const { return appearOnBoard; }
	int getOnBoardCounter() const { return stepsCounter; }
	int getRemainingSteps() const { return length - stepsCounter; }
	int getWaitRand() const { return waitRand; }
	int getwaitCounter() const {return waitCounter; }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setErase(bool res) { erase = res; }
	void setLength(int _length) { length = _length; }
	void setWaitRand(int _waitRand) { waitRand = _waitRand; }
	void setWaitCounter(int _waitCounter) { waitCounter = _waitCounter; }
	void setStart(bool _start) { start = _start; }
	void setStepsCounter(int steps) { stepsCounter = steps; }
	void setAppearOnBoard(bool appear) { appearOnBoard = appear; }
	

};