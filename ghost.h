#pragma once
#include "Creature.h"

class Ghost : public Creature
{
private:
	//-------------------------------------Consts--------------------------------------------------------//
	static constexpr char representativeCh = '$';

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	Ghost(Colors _color = Colors::CYAN, int _x = -1, int _y = -1) :
		Creature(_color, representativeCh, _x, _y) {}
};
