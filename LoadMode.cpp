#include "LoadMode.h"
//-----------------------------------------------------------------------------------------------//
void LoadMode::move()
{
	if (getHoldGhost())
	{
		setHoldGhost(false); // always move the ghost
	}

	SimpleMode::move();
}
//-----------------------------------------------------------------------------------------------//
bool LoadMode::has_Collision()
{
	bool res = RunMode::has_Collision();

	if (res)
	{
		printGame(true);
	}

	return res;
}
//-----------------------------------------------------------------------------------------------//