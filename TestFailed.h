#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class TestFailed
{
private:
	//-----------------------------------------Data Members----------------------------------------------//
	string message;

public:
	//-----------------------------------Public Member Functions-----------------------------------------//

	TestFailed(const string& msg) : message(msg) {}

	void printMessage() const { cout << message; }

};

