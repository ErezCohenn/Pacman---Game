#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "io_utils.h"
using std::string;
using std::cout;
using std::endl;
using std::vector;

class ExceptionBoard
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	vector<string> messages;
	string screenName;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	ExceptionBoard(const string& msg, const string& screen) : screenName(screen){ messages.push_back(msg); }
	ExceptionBoard() : messages(0) {};

	void printExceptions() const;
	void clear() { messages.clear(); }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setMessage(const string& msg) { messages.push_back(msg); }
	void setScreenName(const string& screen) { screenName = screen; }

	//--------------------------------------Get Functions------------------------------------------------//
	size_t getSize() const { return messages.size(); }
	const vector<string>& getMessages() const { return messages; }
	const string& getMessage(int ind) const { return messages[ind]; }
	
	

};

