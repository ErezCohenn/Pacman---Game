#pragma once
#include "RunMode.h"
#include "UserInterface.h"


//---Forward Declaration---//
class Strategy;
class RandomStrategy;
class SmartStrategy;

class SimpleMode : virtual public RunMode
{
public:
	//-------------------------------------Enums---------------------------------------------------------//
	enum LEVELS { NOVICE = 1, GOOD = 2, BEST = 3};
	enum {ESC = 27, GET_OUT = 'G'};
	enum { RUN = '1', COLORS = '2', LEVEL = '3', SPEED = '4', INSTRUCTIONS = '8', EXIT = '9' };
	enum {SLOW = '1', REGULAR = '2', FAST = '3' };

private:
	//-----------------------------------------Data Members----------------------------------------------//

	Strategy* strategy = nullptr;
	UserInterface UI;
	bool input;

	//-----------------------------------Private Member Functions-----------------------------------------//
	char MainMenu();
		
protected:
	//-----------------------------------Protected Member Functions-----------------------------------------//
	
	//Game management
	void printGame(bool collapsed) const;
	virtual bool has_Collision() override;
	virtual int finishGame() override;
	virtual bool startGame() override;
	virtual void init(bool start_screen, bool start_game) override;
	virtual void move() override;

	//handle ghost
	virtual void moveGhosts() override;

	//handle fruit
	virtual bool startFruit(char& value, Point& initP)	override;
	virtual bool eraseFruit() override;
	virtual const Point& getFruitNextStep() override;

	//handle player input
	virtual void getInputs() override;
	
public:
	//-----------------------------------Public Member Functions-----------------------------------------//

	SimpleMode(): input(true)
	{
		setLevel(NOVICE);
		setSpeed(REGULAR);
	}
		
	SimpleMode(const SimpleMode&) = delete;
	SimpleMode& operator=(const SimpleMode&) = delete;
	~SimpleMode() { delete strategy; strategy = nullptr; }

	virtual void Game() override;

	//--------------------------------------Get Functions------------------------------------------------//
	
	bool getInput() const { return input; }
		
	//--------------------------------------Set Functions-----------------------------------------------//
	
	void setInput(bool _input) { input = _input; }
	void setLevel(int level);
	virtual void setSpeed(int _speed) override;

	
};

