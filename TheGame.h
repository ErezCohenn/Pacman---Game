#pragma once
#include "RunMode.h"
#include "SimpleMode.h"
#include "saveMod.h"
#include "SilentMode.h"
#include "LoadMode.h"

class TheGame
{
public:
	//-------------------------------------Consts---------------------------------------------------------//

	const string LOAD = "-load";
	const string SAVE = "-save";
	const string SILENT = "-silent";

private:
	//-----------------------------------------Data Members----------------------------------------------//

	RunMode* mode;
	vector<string> argv;
	int argc;
	
public:
	//-----------------------------------Public Member Functions-----------------------------------------//

	TheGame(int _argc, const char* _argv[]);
	
	TheGame(const TheGame&) = delete;
	TheGame& operator=(const TheGame&) = delete;
	virtual ~TheGame();

	void start();
};

