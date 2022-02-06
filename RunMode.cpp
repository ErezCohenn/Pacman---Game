#include "RunMode.h"
//-----------------------------------------------------------------------------------------------//
bool RunMode::isValidFile(const string& fileName)
{
	ifstream file(fileName);
	string extension = ".screen";

	if (!file.is_open())
	{
		return false;
	}

	size_t ind = fileName.size() - extension.size();

	for (unsigned int i = 0; i < extension.size(); i++)
	{
		if (ind >= fileName.size() || fileName[ind] != extension[i])
		{
			return false;
		}

		ind++;
	}

	return true;
	
}
//-----------------------------------------------------------------------------------------------//
void RunMode::run()
{
	if (!startGame()) // couldnt open the screen
	{
		if ((++indexScreen) == screensFiles.size()) // no more screens to run
		{
			cout << "\nThere is no more screens to run!" << endl << "Press any key to return to the main menu...";
			_getch();
			return;
		}
		else
		{
			cout << "\nPress any key to continue to the next screen...";
			_getch();
			run();
			return;
		}
	}

	if (has_Collision())
	{
		throw ExceptionBoard("Error: cannot play the game, the pacman and on of the ghosts is in the same place", screensFiles[indexScreen]);
	}

	do {

		Sleep(speed);

		getInputs();

		move(); // move characters

		FruitCollision();

		// the pacman collapse with one of the ghosts
		if (has_Collision())
		{
			init(false, false); //init board without breadcrunbs
			player.lostLife();
		}


	} while (player.getRemainLives() > 0 && board.getTotalScore() > 0);

	if (finishGame() == NEXT_SCREEN)
	{
		run(); // run the next screen
		return;
	}
	else
	{
		return; // no more screens to run
	}

}
//-----------------------------------------------------------------------------------------------//
void RunMode::countScreens()
{
	int invalidScreens = 0;
	vector<string> inValidNames;
	const fs::path pathToShow = fs::current_path();

	for (const auto& entry : fs::directory_iterator(pathToShow))
	{
		auto filenameStr = entry.path().filename().string();

		if (entry.is_regular_file())
		{
			if (filenameStr.find(".screen") != string::npos)
			{
				if (isValidFile(filenameStr))
				{
					screensFiles.push_back(static_cast<string>(filenameStr));
				}
				else
				{
					invalidScreens++;
					inValidNames.push_back(filenameStr);
				}
			}
		}
	}
	
	sort(screensFiles.begin(), screensFiles.end());
}
//-----------------------------------------------------------------------------------------------//
void RunMode::init(bool start_screen, bool start_game)
{
	if (start_game)
	{
		if(!specificScreen) // receiving screens from the working directory
		{
			countScreens();
		}

		if (screensFiles.size() == 0)
		{
			clear_screen();
			throw "There is no any valid File found!";
		}

		else
		{
			indexScreen = 0;
		}
	}

	if (start_screen)
	{
		clear_screen();

		board.initBoard(screensFiles[indexScreen]);

		ghosts.clear();
		ghosts.resize(board.getGhostCounter());
		//set init point for all the creaturs

		for (int i = 0; i < board.getGhostCounter(); i++)
		{
			ghosts[i].setInitPoint(board.getLocation(i + 1));
		}

		player.setInitPoint(board.getLocation(0));
		fruit.setStart(true);

		key = 's';
		countSteps = 0;
	}

	// init only characters
	for (unsigned int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].init(start_screen);
	}

	player.init(start_screen, start_game);

	holdGhost = true;

}
//-----------------------------------------------------------------------------------------------//
void RunMode::FruitCollision()
{
	for (unsigned int i = 0; i < ghosts.size(); i++) // check if the ghost ate the fruit
	{
		if (fruit.getCurr() == ghosts[i].getCurr() || fruit.getLast() == ghosts[i].getCurr() && fruit.getCurr() == ghosts[i].getLast())
		{
			fruit.eraseFromBoard(); // the fruit should get erased
			return;

		}

	}

	if (fruit.getCurr() == player.getCurr() || fruit.getLast() == player.getCurr() && fruit.getCurr() == player.getLast()) // check if the pacman ate the fruit
	{
		int res = fruit.getRepresentiveCh() - '0';
		player.setScore(player.getScore() + res);

		fruit.eraseFromBoard();
	}
}
//-----------------------------------------------------------------------------------------------//
bool RunMode::has_Collision()
{
	for (unsigned int i = 0; i < ghosts.size(); i++)
	{
		if (player.getCurr() == ghosts[i].getCurr())
			return true;
		else if (player.getLast() == ghosts[i].getCurr() && player.getCurr() == ghosts[i].getLast()) // pacman and ghosts switched places
			return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------//
bool RunMode::startGame()
{
	try
	{
		init(true, false);
		return true;
	}

	catch (const ExceptionBoard& message)
	{
		message.printExceptions();

		return false;
	}
}
//-----------------------------------------------------------------------------------------------//
int RunMode::finishGame()
{
	if (player.getRemainLives() == 0) // player LOST
	{
		return LOST; //player lost, the game is finished
	}
	
	else if (!specificScreen && (++indexScreen < screensFiles.size()))   // run the next screen
	{
		return NEXT_SCREEN; // didnt finished
	}
	else
	{
		return WON; // player won, but no more screens to run
	}
}
//-----------------------------------------------------------------------------------------------//
void RunMode::moveFruit()
{
	if (!fruit.isAppearOnBoard()) // the fruit is not alive
	{
		Point initP;
		char value;
		
		if(startFruit(value, initP))
		{
			fruit.init(value, initP);
		}

		else
		{
			fruit.setWaitCounter(fruit.getwaitCounter() + 1);
		}
	}
	else //the fruit is alive
	{
		if (eraseFruit())
		{
			fruit.eraseFromBoard();
		}
		else
		{
			Point nextStep = getFruitNextStep();
			
			fruit.move(board, nextStep);
		}
	}
}
//-----------------------------------------------------------------------------------------------//
void RunMode::move()
{
	if (!holdGhost) //move all creatures
	{
		moveGhosts();
		
		holdGhost = true; // next time ghost will not move
	}

	else // move only pacman
	{
		holdGhost = false; // next time ghost will move
	}

	moveFruit();
	player.setDirection(key); // move player
	player.move(board);

	countSteps++;

}
//-----------------------------------------------------------------------------------------------//
