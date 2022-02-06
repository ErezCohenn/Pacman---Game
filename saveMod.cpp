#include "saveMod.h"
//-----------------------------------------------------------------------------------------------//
void SaveMode::writeCreaturesSteps()
{
	ofstream stepsFile(stepsName, std::ios_base::app);

	stepsFile << "Pacman:" << getKey() << " ";

	stepsFile.flush();

	for (int i = 0; i < ghosts.size(); i++) // write steps for ghosts
	{
		stepsFile << "Ghost" << i << ":";

		if (tempHoldGhost) // dont move the ghost 
		{
			stepsFile << Creature::dirStr[Creature::STAY] << "  ";
		}

		else
		{
			stepsFile << findDirection(ghosts[i]) << " ";
		}
	}

	stepsFile << "Fruit:";

	if (fruit.isAppearOnBoard() && fruit.getOnBoardCounter() == 0) // the fruit just appeard 
	{
		stepsFile << "START|" << fruit.getRepresentiveCh() << "|" << "(" << fruit.getCurr().get_Y() << "," << fruit.getCurr().get_X() << ")";

	}
	else if (fruit.isAppearOnBoard()) // the fruit is alive
	{
		stepsFile << "ON|" << findDirection(fruit);
	}
	else // no any fruit on board
	{
		stepsFile << "OFF";
	}

	stepsFile << endl;

	stepsFile.close();
}
//-----------------------------------------------------------------------------------------------//
const string SaveMode::findDirection(const Creature& creature) const
{
	for (int j = 0; j < Creature::SIZE; j++)
	{
		if (creature.getLast() + Creature::directions[j] == creature.getCurr()) //check the next direction 
		{
			if (Creature::dirStr[j] == "UP") // uniformity direction len word (len = 5)
			{
				return Creature::dirStr[j] + "   ";
			}
			else if (Creature::dirStr[j] != "RIGHT")// uniformity direction len word (len = 5)
			{
				return Creature::dirStr[j] + " ";
			}
			else // direction == "RIGHT"
			{
				return Creature::dirStr[j];
			}
		}
	}

	throw TestFailed("Error: invalid direction!");
}
//-----------------------------------------------------------------------------------------------//
int SaveMode::finishGame()
{
	ofstream resFile(resName, std::ios_base::app);


	resFile << "The pacman finished the screen after: " << getCountSteps() << " steps" << endl;

	resFile.close();

	return SimpleMode::finishGame();
}
//-----------------------------------------------------------------------------------------------//
bool SaveMode::has_Collision()
{
	if (SimpleMode::has_Collision())
	{
		ofstream resFile(resName, std::ios_base::app);

		resFile << "The pacman died after: " << getCountSteps() << " steps" << endl;

		resFile.close();

		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------//
void SaveMode::move()
{
	tempHoldGhost = getHoldGhost();

	SimpleMode::move();

	writeCreaturesSteps();

}
//-----------------------------------------------------------------------------------------------//
void SaveMode::init(bool start_screen, bool start_game)
{
	if (start_screen)
	{
		resName = screensFiles[getIndexScreen()].substr(0, screensFiles[getIndexScreen()].size() - 6) + "result"; //create result file
		stepsName = screensFiles[getIndexScreen()].substr(0, screensFiles[getIndexScreen()].size() - 6) + "steps"; //create steps file

		ofstream resFile(resName);
		ofstream stepsFile(stepsName);

		if (!resFile.is_open())
		{
			if (!stepsFile.is_open())
			{
				throw TestFailed("Error: Could not opened result  and steps file for " + screensFiles[getIndexScreen()]);
			}

			throw TestFailed("Error: Could not opened result file for " + screensFiles[getIndexScreen()]);
		}
	}

	SimpleMode::init(start_screen, start_game);
}
//-----------------------------------------------------------------------------------------------//