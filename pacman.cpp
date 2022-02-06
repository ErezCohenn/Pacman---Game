#include "pacman.h"
//-----------------------------------------------------------------------------------------------//
const char pacMan::KEYS[] = { 'A', 'D', 'W', 'X', 'S' };
//-----------------------------------------------------------------------------------------------//
void pacMan::setDirection(char ch)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (ch == keys[i] || ch == keys[i] + 32)
		{
			Creature::setDirection(i);
		}
	}
}
//-----------------------------------------------------------------------------------------------//
void pacMan::lostLife()
{
	if (lives > 0)
	{
		lives--;
	}
}
//-----------------------------------------------------------------------------------------------//
void pacMan::init(bool start_screen, bool start_game)
{
	if (start_game)
	{
		lives = 3;
		score = 0;
	}

	Creature::init(start_screen);
}
//-----------------------------------------------------------------------------------------------//
void pacMan::move(Board& board)
{
	Point nextStep = getDirection();

	// check if the packman move into tunnel
	if (getCurr().get_X() == 1 && getDirection() == Creature::directions[LEFT] && board.getCellVal(getCurr().get_Y(), getCurr().get_X() - 1) == Board::WHITE_SPACE && board.getCellVal(getCurr().get_Y(), board.getLineLen() - 1) == Board::WHITE_SPACE) // if he goes left
	{
		nextStep.set_Y(getCurr().get_Y());
		nextStep.set_X(board.getLineLen() - 2);
	}
	else if (getCurr().get_X() == board.getLineLen() - 2 && getDirection() == Creature::directions[RIGHT] && board.getCellVal(getCurr().get_Y(), getCurr().get_X() + 1) == Board::WHITE_SPACE && board.getCellVal(getCurr().get_Y(), 0) == Board::WHITE_SPACE) // if he goes right
	{
		nextStep.set_Y(getCurr().get_Y());
		nextStep.set_X(1);
	}
	else if (getCurr().get_Y() == 1 && getDirection() == Creature::directions[UP] && board.getCellVal(0, getCurr().get_X()) == Board::WHITE_SPACE && board.getCellVal(board.getRowNumber() - 1, getCurr().get_X()) == Board::WHITE_SPACE) // if he goes up
	{
		nextStep.set_Y(board.getRowNumber() - 2);
		nextStep.set_X(getCurr().get_X());
	}
	else if (getCurr().get_Y() == board.getRowNumber() - 2 && getDirection() == Creature::directions[DOWN] && board.getCellVal(getCurr().get_Y() + 1, getCurr().get_X()) == Board::WHITE_SPACE && board.getCellVal(0, getCurr().get_X()) == Board::WHITE_SPACE) // if he goes Down
	{
		nextStep.set_Y(1);
		nextStep.set_X(getCurr().get_X());

	}
	else // dont move into tunnel
	{
		nextStep = getCurr() + getDirection();
	}

	if (isValidMovePacman(board, nextStep)) // check if the move of the player is valid 
	{
		Creature::move(nextStep);
	}
}
//-----------------------------------------------------------------------------------------------//
bool pacMan::isValidMovePacman(Board& board, const Point& p)
{
	if (board.isValidMove(p))
	{
		unsigned char typeChar = board.getCellVal(p.get_Y(), p.get_X()); // get board char for the next move

		if (typeChar == Board::BREADCRUMBS)
		{
			score++;
			board.setTotalScore();
			try { board.setCellVal(p.get_Y(), p.get_X(), board.WHITE_SPACE); } // set white space instead of breadcrumbs
			catch(ExceptionBoard message)
			{
				cout << message.getMessage(0);
			}
		}

		return true;
	}

	return false;
	// else there is a wall in the next move
}
//-----------------------------------------------------------------------------------------------//