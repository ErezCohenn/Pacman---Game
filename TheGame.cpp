#include "TheGame.h"
//-----------------------------------------------------------------------------------------------//
TheGame::TheGame(int _argc, const char* _argv[])
{
	mode = nullptr;
	argc = _argc;

	for (int i = 1; i < argc; i++)
	{
		argv.push_back(_argv[i]);
	}
}
//-----------------------------------------------------------------------------------------------//
void TheGame::start()
{
	if (argc != 1 && argc != 2 && argc != 3)
	{
		cout << "Error: invalid command line inputs!";
		return;
	}

	if (argc == 1) // no any input
	{
		mode = new SimpleMode;
	}
	
	else if (argv[0] == SAVE)
	{
		if (argc == 2 || argv[1] == SILENT)
		{
			mode = new SaveMode;
		}
		else //the second input is invalid
		{
			cout << "Error: invalid command line inputs!";
			return;
		}
	}

	else if (argv[0] == LOAD)
	{
		if (argc == 2)
		{
			mode = new LoadMode;
		}
		
		else if (argv[1] == SILENT)
		{
			mode = new SilentMode;
		}
		
		else // the second input is invalid
		{
			cout << "Error: invalid command line inputs!";
			return;
		}
	}

	else // the first input us not load or save
	{
		cout << "Error: invalid command line inputs!";
		return;
	}

	clear_screen();

	mode->Game(); // start the game mode that was choosen
}
//-----------------------------------------------------------------------------------------------//
TheGame::~TheGame()
{
	if (mode)
	{
		delete mode;
	}

	mode = nullptr;
}
//-----------------------------------------------------------------------------------------------//
