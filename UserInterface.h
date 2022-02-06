#pragma once
#include "io_utils.h"
#include "ghost.h"
#include "pacman.h"
#include "Strategy.h"
#include <iostream> 
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class UserInterface
{
	//-----------------------------------------Data Members----------------------------------------------//
	string fileName;
	const Colors menuColor = Colors::BROWN;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	void printMenu(bool color)const;
	void showInstructions(bool color)const;
	int levelGame(bool color) const;
	char speedGame(bool color) const;
	void pasue(int x, int y, bool color) const;
	int want_To_Exit(int x, int y, bool color) const;
	void lost_Announcement(int lives, int x, int y, bool color) const;
	void printFinishGame(const char* message, int score, bool color, bool input) const;
	char gameMode(bool color) ;
	bool gameColor(bool color) const;
	void startScreen() const;
	void invalidNotice(const int invalidScreens, const vector<string>& inValidNames)const;

	//--------------------------------------Get Functions------------------------------------------------//
	const string& getFileName() const {return fileName; }
	
	//--------------------------------------Set Functions-----------------------------------------------//
	void setFileName(const string& str) { fileName = str; }
};