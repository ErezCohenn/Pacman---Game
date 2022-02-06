#include "Fruit.h"
//-----------------------------------------------------------------------------------------------//
void Fruit::move(const Board& board, const Point& nextStep)
{
	if (board.isValidMove(nextStep) && stepsCounter % 3 == 0) //move the fruit every 3 steps
	{
		Creature::move(nextStep);
	}

	stepsCounter++;
}
//-----------------------------------------------------------------------------------------------//
void Fruit::init(char value, const Point& initP)
{
	stepsCounter = 0;
	appearOnBoard = true;
	waitCounter = 0;
	start = false;
	erase = false;
	setInitPoint(initP);
	setRepresentiveCh(value);

	Creature::init(true);
}
//-----------------------------------------------------------------------------------------------//
void Fruit::eraseFromBoard()
{
	stepsCounter = 0;
	erase = true;
	appearOnBoard = false;
	start = true;
}
//-----------------------------------------------------------------------------------------------//