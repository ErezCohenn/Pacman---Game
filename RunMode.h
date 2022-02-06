#pragma once
#include <iostream>
#include <cstring>
#include <Windows.h>
#include "io_utils.h"
#include "board.h"
#include "pacman.h"
#include "ghost.h"
#include "point.h"
#include "UserInterface.h"
#include <vector>
#include <string>
#include <filesystem>
#include "Fruit.h"
#include <fstream>
#include <array>

using std::array;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::sort;
namespace fs = std::filesystem;

class RunMode
{
public:
	//-------------------------------------Enums---------------------------------------------------------//
	enum {MAX_GHOST_SIZE = 4 };
	enum {LOST = 0, WON = 1 , NEXT_SCREEN = 2};
	const Point NULL_POINT = { -1, -1 };

private:
	//-----------------------------------------Data Members----------------------------------------------//

	char key; // key for user input
	int countSteps;
	bool specificScreen;
	int speed;
	bool color;
	bool holdGhost;
	int indexScreen;

protected:
	//-----------------------------------------Data Members----------------------------------------------//
	pacMan player;
	Fruit fruit;
	vector<Ghost> ghosts;
	Board board;
	vector<string> screensFiles;
		

	//-----------------------------------Private Member Functions-----------------------------------------//	
	void countScreens();
	void FruitCollision();
	void run();
	bool isValidFile(const string& fileName = "");

protected:
	//----------------------------------Protected Member Functions----------------------------- ----------//	
	
	//Game management
	virtual void init(bool start_screen, bool start_game);
	virtual bool startGame();
	virtual void move();
	virtual bool has_Collision();
	virtual int finishGame();

	//handle ghosts
	virtual void moveGhosts() = 0;
	
	//handle fruit
	virtual void moveFruit();
	virtual bool startFruit(char& value, Point& initP) = 0;
	virtual bool eraseFruit() = 0;
	virtual const Point& getFruitNextStep() = 0;

	//handle player input
	virtual void getInputs() = 0;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	RunMode() : holdGhost(true), indexScreen(0), color(false), speed(0), specificScreen(false) , key('s') , countSteps(0){}

	virtual void Game() = 0;
	virtual ~RunMode() {};

	//--------------------------------------Get Functions------------------------------------------------//
	
	char getKey() const { return key; }
	int getCountSteps() const { return countSteps; }
	bool isSpecificScreen() const { return specificScreen; }
	int getSpeed() const { return speed; }
	bool getColor() const { return color; }
	bool getHoldGhost() const { return holdGhost; }
	int getIndexScreen() const { return indexScreen; }

	//--------------------------------------Set Functions------------------------------------------------//

	void setKey(char _key) { key = _key; }
	void setCountSteps(int _count) { countSteps = _count; }
	void setSpecificScreen(bool _specific) { specificScreen = _specific; }
	virtual void setSpeed(int _speed) { speed = _speed; }
	void setColor(bool _color) { color = _color; }
	void setHoldGhost(bool hold) { holdGhost = hold; }
	void setIndexScreen(int index) { indexScreen = index; }
};