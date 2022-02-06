#pragma once
#include "point.h"
#include "Colors.h"
#include <iostream>
#include "board.h"
#include "io_utils.h"

using std::cout;

class Creature
{
public:
	//-------------------------------------Enums & Consts-------------------------------------------------//
	enum { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, STAY = 4, SIZE };
	const static vector<string> dirStr;
	const static Point directions[SIZE];

private:
	//-------------------------------------Data Members--------------------------------------------------//
	Point initP;
	Point curr, last;
	Point direction;
	char representativeCh;
	Colors color;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	Creature(Colors _color, char ch, int _x = -1, int _y = -1) :
	curr(_x, _y), last(_x, _y), initP(_x, _y), direction(STAY), color(_color)
	{
		setRepresentiveCh(ch);
	};

	void print(bool gameColor) const;
	void init(bool start);
	void move(const Point& nextStep);
	
	//--------------------------------------Get Functions-----------------------------------------------//
	const Point& getDirection() const { return direction; }
	const Point& getCurr()const { return curr; }
	const Point& getLast()const { return last; }
	const Point& getInitPoint() const { return initP; }
	char getRepresentiveCh() const { return representativeCh; }
	Colors getColor() const { return color; }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setDirection(int ind) { direction = directions[ind]; }
	void setDirection(const Point& dir) { direction = dir; }
	void setCurr(const Point& p) { curr = p; }
	void setLast(const Point& p) { last = p; }
	void setInitPoint(const Point& p) { initP = p; }
	void setRepresentiveCh(char ch) { representativeCh = ch; }
	void setColor(Colors c) { color = c; }
};