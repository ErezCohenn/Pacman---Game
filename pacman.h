#pragma once
#include <iostream>
#include "board.h"
#include "Creature.h"

using std::cout;

class pacMan : public Creature
{
public:
	//-------------------------------------Consts--------------------------------------------------------//
	static const char KEYS[];
	static constexpr char representativeCh = '@';

private:
	//-----------------------------------------Data Members----------------------------------------------//
	char keys[SIZE];
	int lives;
	int score;
	
public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	pacMan(Colors _color = Colors::BROWN, int _x = -1, int _y = -1) :
	Creature(_color, representativeCh, _x, _y), lives(3), score(0)
	{
		for (int dir = 0; dir < SIZE; dir++)
		{
			keys[dir] = KEYS[dir];
		}
	}

	void lostLife();
	void init(bool start_screen, bool start_game);
	void move(Board& board);
	bool isValidMovePacman(Board& board, const Point& p);

	//--------------------------------------Get Functions------------------------------------------------//
	int getRemainLives()const { return lives; }
	int getScore() const { return score; }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setDirection(char ch);
	void setScore(int _score) { score = _score; }

	

};
