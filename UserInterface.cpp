#include "UserInterface.h"
//-----------------------------------------------------------------------------------------------//
void UserInterface::printMenu(bool color) const {

	gotoxy(20, 0);

	if (color)
	{
		setTextColor(menuColor);
	}

	cout << "\n        Welcome to the Pacman Game !!! \n\
    Please select one of the options below:" << endl;
	cout << "  ---------------------------------------------\n  |";
	cout << "                Main Menu                  ";
	cout << "|\n  |                                           |\n\
  |-------------------------------------------|\n  |";
	cout << " 1.  Start A New Game                      ";
	cout << "|\n  |-------------------------------------------|\n  |";
	cout << " 2.  Choose a color                        ";
	cout << "|\n  |-------------------------------------------|\n  |";
	cout << " 3.  Choose a level                        ";
	cout << "|\n  |-------------------------------------------|\n  |";
	cout << " 4.  Choose a speed                        ";
	cout << "|\n  |-------------------------------------------|\n  |";
	cout << " 8.  Present instructions and keys         ";
	cout << "|\n  |-------------------------------------------|\n  |";
	cout << " 9.  Exit                                  ";
	cout << "|\n  |-------------------------------------------|\n";

}
//-----------------------------------------------------------------------------------------------//
int UserInterface::levelGame(bool color) const
{
	clear_screen();
	Strategy* level = nullptr;

	if (color)
	{
		setTextColor(menuColor);
	}


	cout << "Please choose your level that you want to play in the game: " << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "1. Novice\n2. Good\n3. Best" << endl;

	char res = _getch();

	while (res != '1' && res != '2' && res != '3')
	{
		gotoxy(0, 5);
		cout << "Invalid choise " << endl;
		res = _getch();
	}

	clear_screen();

	return (res - '0');

}
//-----------------------------------------------------------------------------------------------//
char UserInterface::speedGame(bool color) const
{
	clear_screen();

	if (color)
	{
		setTextColor(menuColor);
	}

	cout << "Please enter the speed of the game:\n";
	cout << "----------------------------------\n";
	cout << "1. slow\n";
	cout << "2. average\n";
	cout << "3. fast";

	char res = _getch();

	while (res != '1' && res != '2' && res != '3')
	{
		gotoxy(0, 5);
		cout << "Invalid choice!";

		res = _getch();
	}

	clear_screen();

	return res;
}
//-----------------------------------------------------------------------------------------------//
void UserInterface::showInstructions(bool color) const
{
	clear_screen();
	gotoxy(20, 0);
	cout << "\
Instructions:\n\
The player must navigate the pacman (the character - @) through a maze while\n\
eating the breadcrumbs. Each eaten breadcrumb equals a point to be earned.\n\
Once all breadcrumbs on screen are eaten, the game ends and you won the game!\n\
In addition, two ghosts roam around the maze in order to catch the Pacman\n\
(the character - $). In case a ghost eats the Pacman, you lost one life.\n\
Pacman has a total of 3 lives, and if all lives are gone you lost the game!\n";

	if (color)
	{
		setTextColor(menuColor);
	}

	cout << "  	         --------------------\n\
	         |     	Keys:       |\n\
	         --------------------\n\
                 | LEFT    | a or A |\n\
                 --------------------\n\
                 | RIGHT   | d or D |\n\
                 --------------------\n\
                 | UP      | w or W |\n\
                 --------------------\n\
                 | DOWN    | x or X |\n\
                 --------------------\n\
                 | STAY    | s or S |\n\
                 --------------------\n\
                 | Get out | g or G |\n\
                 --------------------\n\
                 | PAUSE   | ESC    |\n\
                 --------------------\n";

	cout << "             < Press any key to return >";

	_getch();
	clear_screen();
}
//-----------------------------------------------------------------------------------------------//
void UserInterface::pasue(int x, int y, bool color) const
{
	gotoxy(x, y);

	if (color)
	{
		setTextColor(menuColor);
	}

	cout << "Game paused, press";
	gotoxy(x, y + 1);
	cout << "ESC to continue...";
	gotoxy(x, y + 2);
	cout << "                    ";
	while (!_kbhit || _getch() != 27) // ESC = 27
	{
		gotoxy(x, y + 2);
		cout << "Invalid choise    " << endl;
		//do nothing until press ESC again to resume the game
	}

	gotoxy(x, y);
	cout << "                   ";
	gotoxy(x, y + 1);
	cout << "                   ";
	gotoxy(x, y + 2);
	cout << "                   ";
}
//-----------------------------------------------------------------------------------------------//
void UserInterface::invalidNotice(const int invalidScreens, const vector<string>& inValidNames) const
{
	clear_screen();
	gotoxy(0, 0);
	cout << "Just to let you know, there are " << invalidScreens << " invalid screens in your directory." << endl;
	cout << "their names are : \n" << endl;
	for (int i = 0; i < invalidScreens; i++)
	{
		cout << inValidNames[i] << endl << endl;
	}
	cout << "Please press any key to continue" << endl;
	_getch();
	clear_screen();
}
//-----------------------------------------------------------------------------------------------//
int UserInterface::want_To_Exit(int x, int y, bool color) const
{
	if (color)
	{
		setTextColor(Colors::WHITE);
	}

	gotoxy(x, y);
	cout << "Wait ! are you sure";
	gotoxy(x, y + 1);
	cout << "you want to EXIT ? ";
	gotoxy(x, y + 2);
	cout << "1.yes   2.no ";
	char key = _getch();
	while (key != '2' && key != '1')
	{
		gotoxy(x, y);
		cout << "                   ";
		gotoxy(x, y + 1);
		cout << "                   ";
		gotoxy(x, y + 2);
		cout << "Invalid choise";
		key = _getch();
	}
	if (key == '1')
	{
		return 1;
	}
	else
	{
		gotoxy(x, y);
		cout << "                   ";
		gotoxy(x, y + 1);
		cout << "                   ";
		gotoxy(x, y + 2);
		cout << "                   ";
		return 0;
	}
}
//-----------------------------------------------------------------------------------------------//
void UserInterface::lost_Announcement(int lives, int x, int y, bool color) const // when the player lose the screen stops and he gets a massege
{
	gotoxy(x, y);

	if (color)
	{
		setTextColor(Colors::WHITE);
	}

	cout << "You crossed a ghost";
	gotoxy(x, y + 1);
	cout << "Press any key  ";
	gotoxy(x, y + 2);
	cout << "to continue...";

	while (!_kbhit())
	{
		//do nothing until press any key again to resume the game
	}

	gotoxy(x, y);
	cout << "                   ";
	gotoxy(x, y + 1);
	cout << "                   ";
	gotoxy(x, y + 2);
	cout << "                   ";
}
//-----------------------------------------------------------------------------------------------//
void UserInterface::printFinishGame(const char* message, int score, bool color, bool input) const
{
	clear_screen();

	if (color)
	{
		setTextColor(menuColor);
	}
	cout << "----------------------------------------------------------\n\|";

	if (message == "LOST")
	{
		cout << "                                                        |\n|                      YOU " << message << " !!!                      ";
	} 
	else if (message == "WON") // message == WON (one more space for frame)
	{
		cout << "                                                        |\n|                      YOU " << message << " !!!                       ";
	}
	else// won only spesific map (one more space for frame)
	{
		cout << "                   YOU WON THIS MAP!!!                  |\n|" << "           " << message << "           ";
	}

	cout << "|\n|";

	if (score < 10)
	{
		cout << "                   Your score is : " << score << "                    ";
	}
	else if (score < 100)
	{
		cout << "                   Your score is : " << score << "                   ";
	}
	else

	{
		cout << "                   Your score is : " << score << "                  ";
	}

	cout << "|\n|";
	if (message == "WON" || message == "LOST")
	{
		
		
		cout << "              < Press any key to continue... >          ";
		cout << "|\n|                                                        |\n\
----------------------------------------------------------";

		_getch();
	}
	else
	{
		cout << "      < Press any key to continue to next screen >      ";
		cout << "|\n|                                                        |\n\
----------------------------------------------------------";

		_getch();
	}


	clear_screen();
}
//-----------------------------------------------------------------------------------------------//
char UserInterface::gameMode(bool color)
{
	clear_screen();

	if (color)
	{
		setTextColor(menuColor);
	}

	cout << "Please enter the mode of the game:\n(or press other key to return to the main menu)\n";
	cout << "----------------------------------\n";
	cout << "1. Several of screens\n";
	cout << "2. Specific screen";

	char res = _getch();

	if(res == '2')
	{
		clear_screen();
		gotoxy(0, 0);
		cout << "Please enter the file name of the screen:\n";
		cin >> fileName;
		clear_screen();
	}

	clear_screen();

	return res;
}
//-----------------------------------------------------------------------------------------------//
bool UserInterface::gameColor(bool color) const
{
	bool new_color;
	clear_screen();

	if (color)
	{
		setTextColor(menuColor);
	}

	cout << "\nPlease select one of the option below:" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "(0) If you want to play in Black and White\n(1) If you want to play with COLORS\n";
	cout << "----------------------------------------------------" << endl;
	char res = _getch();

	while (res != '0' && res != '1')
	{
		gotoxy(0, 6);
		cout << "Invalid choise " << endl;
		res = _getch();
	}

	if (res == '0')
	{
		new_color = false;
	}
	else
	{
		new_color = true;
	}

	clear_screen();

	return new_color;

}
//-----------------------------------------------------------------------------------------------//
void UserInterface::startScreen() const
{
	clear_screen();
	
	for (int i = 3; i > 0; i--) // starting screen
	{
		gotoxy(0, 0);

		cout << "Screen starts in " << i << " seconds...";

		Sleep(1000);
	}

	clear_screen();
}
//-----------------------------------------------------------------------------------------------//