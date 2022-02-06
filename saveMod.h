#pragma once
#include "SimpleMode.h"
#include "TestFailed.h"

class SaveMode : public SimpleMode
{
private:
	//-----------------------------------------Data Members----------------------------------------------//

	string resName;
	string stepsName;
	bool tempHoldGhost;
	//-----------------------------------Private Member Functions-----------------------------------------//

	void writeCreaturesSteps();
	const string findDirection(const Creature& creature) const;
	virtual int finishGame() override;
	virtual bool has_Collision() override;
	virtual void move() override;
	virtual void init(bool start_screen, bool start_game) override;
	
public:
	//-----------------------------------Public Member Functions-----------------------------------------//

	SaveMode(): tempHoldGhost(getHoldGhost()){}
};

