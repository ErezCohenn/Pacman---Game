#pragma once
#include "RunMode.h"
#include "TestFailed.h"
#include <typeinfo>

class SilentMode : virtual public RunMode
{
public:
	//-------------------------------------Enums---------------------------------------------------------//

	enum { SIZE_FORMAT_GHOST = 12, SIZE_FORMAT_PACMAN = 8 };

private:
	//-----------------------------------------Data Members----------------------------------------------//

	string resName;
	string stepsName;
	std::streamoff indexStepsFile;
	std::streamoff indexResultFile;

	//-----------------------------------Private Member Functions-----------------------------------------//


	bool isFileOpened(ifstream& fileName);
	bool checkTest(bool finish_game);
	bool isValidGhost(const string& str, int num);
	unsigned char getKey(const string& str) const;
	const Point& getDirection(string&& dir);

protected:
	//-----------------------------------Protected Member Functions-----------------------------------------//

	//Game management
	virtual bool has_Collision() override;
	virtual int finishGame() override;
	virtual void init(bool start_screen, bool start_game) override;
	virtual void move() override;

	//handle ghosts
	virtual void moveGhosts() override;
	
	//handle fruit
	virtual bool startFruit(char& value, Point& initP) override;
	virtual bool eraseFruit() override;
	virtual const Point& getFruitNextStep() override;

	//handle player input
	virtual void getInputs() override;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//

	SilentMode(int _speed = 0) : indexStepsFile(0), indexResultFile(0)
	{
		setSpeed(_speed);
	}

	virtual void Game() override;
};

