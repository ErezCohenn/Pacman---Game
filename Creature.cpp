#include "Creature.h"
//-----------------------------------------------------------------------------------------------//
const Point Creature::directions[SIZE] = { {-1,0}, {1,0}, {0,-1} ,{0,1}, {0,0}};
const vector<string> Creature::dirStr = { "LEFT", "RIGHT", "UP", "DOWN", "STAY" };
//-----------------------------------------------------------------------------------------------//
void Creature::print(bool gameColor) const
{
	gotoxy(curr.get_X(), curr.get_Y());
	
	if (gameColor)
	{
		setTextColor(color);
	}
		
	cout << representativeCh;
}
//-----------------------------------------------------------------------------------------------//
void Creature::init(bool start)
{
	direction = directions[STAY];
	//
	if (start)
	{
		last = initP;
	}
	else
	{
		last = curr;
	}

	curr = initP;
}
//-----------------------------------------------------------------------------------------------//
void Creature::move(const Point& nextStep)
{
	setLast(getCurr());
	setCurr(nextStep);
}
//-----------------------------------------------------------------------------------------------//



