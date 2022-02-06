#include "SimpleMode.h"
#include "Strategy.h"
#include "RandomStrategy.h"
#include "SmartStrategy.h"
#include "MediocreStrategy.h"
//-----------------------------------------------------------------------------------------------//
void SimpleMode::setSpeed(int _speed)
{
	
	if (_speed == SLOW)
	{
		_speed = 100;
	}
	else if (_speed == REGULAR)
	{
		_speed = 75;
	}
	else if (_speed == FAST)
	{
		_speed = 50;
	}

	RunMode::setSpeed(_speed);
}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::init(bool start_screen, bool start_game)
{
	if (start_game)
	{
		screensFiles.clear();
				
		if (isSpecificScreen()) // the user choose to play with specific screen
		{
			string fileName = UI.getFileName();

			if (isValidFile(fileName))
			{
				screensFiles.push_back(fileName);
			}
		}
		
	}
	
	RunMode::init(start_screen, start_game);

	strategy->setCountSteps(0); // initialize countSteps to zero
}
//-----------------------------------------------------------------------------------------------//
int SimpleMode::finishGame()
{
	fruit.eraseFromBoard();

	int res = RunMode::finishGame();

	if (res == LOST)
	{
		UI.printFinishGame("LOST", player.getScore(), getColor(), input);
	}
	else if (res == WON)
	{
		printGame(true);

		UI.printFinishGame("WON", player.getScore(), getColor(), input);
	}
	else // res == NEXT_SCREEN
	{
		UI.printFinishGame("Great Job, See you in the next one", player.getScore(), getColor(), input);
	}

	return res;
}
//-----------------------------------------------------------------------------------------------//
bool SimpleMode::startGame()
{
	bool res = RunMode::startGame();

	if (res)
	{
		UI.startScreen();

		board.printBoard(getColor());

	}

	return res;
}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::Game()
{
	char res;

	hideCursor();

	do {

		res = MainMenu();

	} while (res != EXIT);
}
//-----------------------------------------------------------------------------------------------//
char SimpleMode::MainMenu()
{
	bool validChoice = true;
	char UserChoice;
	
	do {
		hideCursor();
		UI.printMenu(getColor());
		UserChoice = _getch();

		if (UserChoice == RUN)
		{
			char res = UI.gameMode(getColor());

			if (res == '1')
			{
				setSpecificScreen(false);
			}
			else if (res == '2')
			{
				setSpecificScreen(true);
			}
			else // return to main menu
			{
				return UserChoice;
			}

			clear_screen();

			try { init(false, true); run(); } // first init for read all the files in the game
			catch (const char* msg)
			{
				cout << msg << endl;
				cout << "Press any key to return to the main menu...";

				_getch();

				clear_screen();
			}


		}
		else if (UserChoice == COLORS)
		{
			setColor(UI.gameColor(getColor()));
		}
		else if (UserChoice == LEVEL)
		{
			setLevel(UI.levelGame(getColor()));
		}
		else if (UserChoice == SPEED)
		{
			setSpeed(UI.speedGame(getColor()));
		}
		else if (UserChoice == INSTRUCTIONS)
		{
			UI.showInstructions(getColor());
		}
		else if (UserChoice == EXIT)
		{
			return UserChoice;
		}
		else // pressed any other invalid Choice
		{
			gotoxy(8, 17);
			cout << "Invalid choise! Please try again" << endl;
			validChoice = false;
		}

	} while (!validChoice);

	return UserChoice;
}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::printGame(bool collapsed) const
{
	if (getColor())
	{
		setTextColor(Colors::WHITE);
	}

	// prints the cells back after characters cross them
	for (unsigned int i = 0; i < ghosts.size(); i++)
	{
		board.printCell(ghosts[i].getLast().get_X(), ghosts[i].getLast().get_Y());
	}
	board.printCell(player.getLast().get_X(), player.getLast().get_Y());

	if (getColor())
	{
		setTextColor(Colors::WHITE);
	}
	//print Data
	gotoxy(board.getLegend_x(), board.getLegend_y());
	cout << " Score: " << player.getScore() << endl;
	gotoxy(board.getLegend_x(), board.getLegend_y() + 1);
	cout << " Lives left : " << player.getRemainLives();

	if (fruit.getIserased()) // if the fruit just died print the last cell board
	{
		board.printCell(fruit.getLast().get_X(), fruit.getLast().get_Y());
		board.printCell(fruit.getCurr().get_X(), fruit.getCurr().get_Y());
	}

	else if (fruit.isAppearOnBoard() == 1 && fruit.getLast() != NULL_POINT)// if there is a fruit on board
	{
		board.printCell(fruit.getLast().get_X(), fruit.getLast().get_Y());
		fruit.print(getColor());
	}
	
	if (!collapsed)
	{
		player.print(getColor());
	}
	for (unsigned int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].print(getColor());
	}
}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::moveGhosts()
{
	if (!getHoldGhost())
	{
		strategy->strategyMove(board, ghosts, player.getCurr());
	}

}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::move()
{
	printGame(false);

	RunMode::move();
}
//-----------------------------------------------------------------------------------------------//
bool SimpleMode::startFruit(char& value, Point& initP)
{

	if (fruit.getStart()) // if there is no fruit on board and no initalization
	{
		fruit.setWaitRand(rand() % 40); // turns to wait untill the fruit shows
		fruit.setLength(rand() % 220 + 150); // how long the next fruit is going to show
		fruit.setStart(false);
	}

	if (fruit.getwaitCounter() >= fruit.getWaitRand())
	{
		int index = rand() % (board.getOptionalIndex()); //get a random index to choose from the points of bread
		initP = board.getAPointForFruit(index);
		value = ('0' + (rand() % 5) + 5);

		return true;
	}
	return false;;
}
//-----------------------------------------------------------------------------------------------//
bool SimpleMode::eraseFruit()
{
	if (fruit.getRemainingSteps() <= 0 || fruit.getIserased())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//-----------------------------------------------------------------------------------------------//
const Point& SimpleMode::getFruitNextStep()
{
	fruit.setDirection(rand() % 4);

	return (fruit.getDirection() + fruit.getCurr());
}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::setLevel(int level)
{
	delete strategy;

	if (level == NOVICE)
	{
		strategy = new RandomStrategy(20);
	}
	else if (level == GOOD)
	{
		strategy = new MediocreStrategy(5);
	}
	else if (level == BEST)
	{
		strategy = new SmartStrategy;
	}
	
	if (!strategy)
	{
		throw "Error to allocate new strategy!";
	}
}
//-----------------------------------------------------------------------------------------------//
void SimpleMode::getInputs()
{
	if (_kbhit())
	{
		setKey(_getch());

		if (getKey() == ESC)
		{
			UI.pasue(board.getLegend_x(), board.getLegend_y(), getColor());
		}
		else if (getKey() == GET_OUT || getKey() == GET_OUT + 32)
		{
			int res = UI.want_To_Exit(board.getLegend_x(), board.getLegend_y(), getColor());

			if (res == 1)
			{
				clear_screen();
				throw "You get out from the game!";
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------//
bool SimpleMode::has_Collision()
{
	bool res = RunMode::has_Collision();

	if (res)
	{
		printGame(true);

		if (player.getRemainLives() > 1) // if the players has more lives
		{
			UI.lost_Announcement(player.getRemainLives() - 1, board.getLegend_x(), board.getLegend_y(), getColor());
		}
	}

	return res;
}
//-----------------------------------------------------------------------------------------------//