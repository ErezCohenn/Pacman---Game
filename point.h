#pragma once

class Point
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	int x , y;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	Point(int _x= -1, int _y= -1) : x(_x), y(_y) {}
	Point operator+(const Point& p2) const { return Point(x + p2.x, y + p2.y); }
	bool operator==(const Point& p2) const { return x == p2.x && y == p2.y; }
	bool operator!=(const Point& p2) const { return x != p2.x || y != p2.y; }
	
	//--------------------------------------Get Functions------------------------------------------------//
	int get_X() const { return x; }
	int get_Y() const { return y; }
	
	//--------------------------------------Set Functions-----------------------------------------------//
	void setCoordinates(int _x, int _y) { x = _x; y = _y; }
	void set_X(int _x) { x = _x; }
	void set_Y(int _y) { y = _y; }

};