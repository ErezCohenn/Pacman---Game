#include "SilentMode.h"
//-----------------------------------------------------------------------------------------------//
void SilentMode::Game()
{
	try 
	{ 
		init(false, true); run();

		string str = typeid(*this).name();
		
		if (str == "class SilentMode")
		{
			cout << "TEST PASSED!!!";
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
	catch (const TestFailed& message)
	{
		clear_screen();
		
		message.printMessage();
	}
}
//-----------------------------------------------------------------------------------------------//
bool SilentMode::isFileOpened(ifstream& fileName)
{
	if (!fileName.is_open())
	{
		return false;
	}
	
	fileName.seekg(indexStepsFile, std::ios::beg);

	string str;
	getline(fileName, str);
	fileName.seekg(indexStepsFile, std::ios::beg);

	if (fileName.tellg() == -1 || str[0] == '\n') // end of file
	{
		indexStepsFile = 0;
		fileName.close();
		return false;
	}

	else
	{
		return true;
	}
}
//-----------------------------------------------------------------------------------------------//
unsigned char SilentMode::getKey(const string& str) const
{
	if (str.substr(0, 7) == "Pacman:")
	{
		return str[7];
	}
	else
	{
		throw TestFailed("Error format pacman: invalid steps screen format for " + screensFiles[getIndexScreen()]);
	}
}
//-----------------------------------------------------------------------------------------------//
bool SilentMode::has_Collision()                                                                                                                                                                                                                                          
{
	bool res = RunMode::has_Collision();

	if (res)
	{
		if (!checkTest(false)) //test failed
		{
			throw TestFailed("Test Failed: points of time for " + screensFiles[getIndexScreen()] + " where pacman died is incorrect!");
		}
	}

	return res;
}
//-----------------------------------------------------------------------------------------------//
int SilentMode::finishGame()
{
	if (!checkTest(true))
	{
		throw TestFailed("Test Failed: point of time for " + screensFiles[getIndexScreen()] + " where pacman finished the screen is incorrect!");
	}

	return RunMode::finishGame();
}
//-----------------------------------------------------------------------------------------------//
bool SilentMode::checkTest(bool finish_game)
{
	ifstream resFile(resName);
	string line;
	
	resFile.seekg(indexResultFile, std::ios::beg);
	getline(resFile, line, '\n');

	if (resFile.tellg() == -1) // end of file
	{
		indexResultFile = 0;
		return false;
	}
	indexResultFile = resFile.tellg();

	if (finish_game) // check the point of time finish screen
	{
		line = line.substr(38);
	}
	else // check the point of time when pacman died
	{
		line = line.substr(23);
	}
		
	return stoi(line) == getCountSteps(); //return if the pacman died after countSteps as excepted in the test file

}
//-----------------------------------------------------------------------------------------------//
void SilentMode::init(bool start_screen, bool start_game)
{
	if(start_game)
	{
		screensFiles.clear();
	}
	
	if (start_screen && getIndexScreen() < screensFiles.size())
	{
		indexStepsFile = 0;
		indexResultFile = 0;

		resName = screensFiles[getIndexScreen()].substr(0, screensFiles[getIndexScreen()].size() - 6) + "result"; //create result file
		stepsName = screensFiles[getIndexScreen()].substr(0, screensFiles[getIndexScreen()].size() - 6) + "steps"; //create steps file

		
		ifstream resFile(resName);
		ifstream stepsFile(stepsName);
		
		if (!resFile.is_open())
		{
			if (!stepsFile.is_open())
			{
				throw TestFailed("Error: Could not opened result  and steps file for " + screensFiles[getIndexScreen()]);
			}
			
			throw TestFailed("Error: Could not opened result file for " + screensFiles[getIndexScreen()]);
		}
		
	}
	
	else if(!start_game && start_screen) // no more screens to run 
	{
		return;
	}

	RunMode::init(start_screen, start_game);
}
//-----------------------------------------------------------------------------------------------//
void SilentMode::getInputs()
{
	string line;

	ifstream stepsFile(stepsName);
	
	if (!isFileOpened(stepsFile))
	{
		return;
	}

	getline(stepsFile, line, ' ');

	if (line.size() != 8)
	{
		throw TestFailed("Error format pacman length: invalid steps screen format for " + screensFiles[getIndexScreen()]);
	}

	setKey(getKey(line));

	stepsFile.close();
}
//-----------------------------------------------------------------------------------------------//
bool SilentMode::startFruit(char& value, Point& initP)
{
	string line;

	ifstream stepsFile(stepsName);
	
	if (!isFileOpened(stepsFile))
	{
		return false;
	}
	getline(stepsFile, line, '\n');

	indexStepsFile = stepsFile.tellg(); //update index for next line

	line = line.substr((SIZE_FORMAT_GHOST + 1) * ghosts.size() + SIZE_FORMAT_PACMAN + 1);

	string temp = line.substr(0, 6);

	if (temp != "Fruit:")
	{
		throw TestFailed("Error: invalid format fruit");
	}

	temp = line.substr(6, 5);

	if (temp == "START")
	{
		int row, col;
		value = line.substr(12, 1)[0];

		// get start (row, col)
		temp = line.substr(15, 5);
		row = stoi(temp);
		temp = temp.substr(std::to_string(row).size() + 1); //substr after comma to get col
		col = stoi(temp);

		initP = { col, row };

		return true;
	}
	else
	{
		return false;
	}
}
//-----------------------------------------------------------------------------------------------//
bool SilentMode::eraseFruit()
{
	string line;

	ifstream stepsFile(stepsName);

	if (!isFileOpened(stepsFile))
	{
		return true;
	}
	getline(stepsFile, line, '\n');

	indexStepsFile = stepsFile.tellg(); //update index for next line

	line = line.substr((SIZE_FORMAT_GHOST + 1) * ghosts.size() + SIZE_FORMAT_PACMAN + 1);

	string temp = line.substr(0, 6);

	if (temp != "Fruit:")
	{
		throw TestFailed("Error: invalid format fruit");
	}

	temp = line.substr(6);

	if (temp.size() == 4 && temp == "OFF")
	{
		return true;
	}
	else
	{
		return false;
	}
}
//-----------------------------------------------------------------------------------------------//
const Point& SilentMode::getFruitNextStep()
{
	string line;

	ifstream stepsFile(stepsName);

	if (!isFileOpened(stepsFile))
	{
		return NULL_POINT;
	}
	getline(stepsFile, line, '\n');

	line = line.substr((SIZE_FORMAT_GHOST + 1) * ghosts.size() + SIZE_FORMAT_PACMAN + 1);

	string temp = line.substr(0, 6);

	if (temp != "Fruit:")
	{
		throw TestFailed("Error: invalid format fruit");
	}

	temp = line.substr(6, 2);

	if (temp.size() == 3 && temp == "ON")
	{
		return (fruit.getCurr() + getDirection(line.substr(9)));
	}
	else
	{
		return NULL_POINT;
	}
}
//-----------------------------------------------------------------------------------------------//
void SilentMode::move()
{
	if (getHoldGhost())
	{
		setHoldGhost(false); // always move the ghost
	}

	RunMode::move();

}
//-----------------------------------------------------------------------------------------------//
void SilentMode::moveGhosts()
{
	string ghost, line;
	ifstream stepsFile(stepsName);
	Point direction, nextStep;

	if (!isFileOpened(stepsFile))
	{
		return;
	}

	getline(stepsFile, line);
	
	line = line.substr(SIZE_FORMAT_PACMAN + 1);

	int index = 0;

	for (int i = 0; i < ghosts.size(); i++)
	{
		if (line.size() < SIZE_FORMAT_GHOST)
		{
			throw TestFailed("Error format ghost length: invalid steps screen format for " + screensFiles[getIndexScreen()]);
		}
		
		ghost = line.substr(index, SIZE_FORMAT_GHOST);

		if (isValidGhost(ghost, i))
		{
			direction = getDirection(ghost.substr(7));

			ghosts[i].setDirection(direction);

			nextStep = ghosts[i].getCurr() + ghosts[i].getDirection();

			ghosts[i].move(nextStep);
		}
		else
		{
			throw TestFailed("Error format ghost: invalid steps screen format for " + screensFiles[getIndexScreen()]);
		}

		index += SIZE_FORMAT_GHOST + 1;
	}

	stepsFile.close();

}
//-----------------------------------------------------------------------------------------------//
bool SilentMode::isValidGhost(const string& str, int num)
{
	string res = "Ghost";
	res.append(1, '0' + num);
	res.append(":");
	return (str.substr(0, SIZE_FORMAT_GHOST - 5) == res); //compare "Ghosti:"
}
//-----------------------------------------------------------------------------------------------//
const Point& SilentMode::getDirection(string&& dir)
{
	if (dir == "UP   ")
	{
		dir = dir.substr(0, 2); // cut the space
	}
	else if (dir == "LEFT " || dir == "DOWN " || dir == "STAY ")
	{
		dir = dir.substr(0,4); //cut the space
	}
	else if (dir != "RIGHT")
	{
		throw TestFailed("Error ghost format direction: invalid steps screen format for " + screensFiles[getIndexScreen()]);
	}

	//else dir == RIGHT, no need to substr

	for (int i = 0; i < Creature::SIZE; i++)
	{
		if (Creature::dirStr[i] == dir)
		{
			return Creature::directions[i];
		}
	}
}
//-----------------------------------------------------------------------------------------------//