#pragma once
#include "SilentMode.h"
#include "SimpleMode.h"
#include "UserInterface.h"

class LoadMode : public SilentMode, public SimpleMode
{
protected:
	//-----------------------------------Protected Member Functions-----------------------------------------//
	virtual void init(bool start_screen, bool start_game) override { SilentMode::init(start_screen, start_game); }
	virtual void move() override;
	virtual bool has_Collision() override;
	virtual int finishGame() override {return SimpleMode::finishGame();}

	//handle ghost
	virtual void moveGhosts() override { SilentMode::moveGhosts(); }

	//handle player input 
	virtual void getInputs() override { SilentMode::getInputs(); }

	//handle fruit
	virtual bool startFruit(char& value, Point& initP) override { return SilentMode::startFruit(value, initP); }
	virtual bool eraseFruit() override { return SilentMode::eraseFruit(); }
	virtual const Point& getFruitNextStep() override { return SilentMode::getFruitNextStep(); }

public:
	//-----------------------------------Public Member Functions-----------------------------------------//

	LoadMode()
	{
		RunMode::setSpeed(SimpleMode::FAST);
		setInput(false);
		setLevel(true);
	}

	virtual void Game() override { SilentMode::Game(); }
};

