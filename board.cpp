#include "board.h"
//-----------------------------------------------------------------------------------------------//
unsigned char Board::getCellVal(int row, int col) const
{
	if ((row >= 0 && row <= ROWS) && (col >= 0 && col <= COLS))
	{
		return board[row][col];
	}

}
//-----------------------------------------------------------------------------------------------//
void Board::setCellVal(int row, int col, unsigned char ch)
{
	if ((row >= 0 && row < ROWS) && (col >= 0 && col < COLS))
	{
		board[row][col] = ch;
	}

}
//-----------------------------------------------------------------------------------------------//
void Board::clearBoard()
{
	for (int i = 0; i < MaxRows; i++)
	{
		for (int j = 0; j < MaxCols; j++)
		{
			board[i][j] = ' ';
		}
	}

	ROWS = COLS = 0;
	TotalScore = 0;
	ghostCounter = 0;
	pacmanCount = 0;
	legendCount = 0;
	exceptionBoard.clear();
}
//-----------------------------------------------------------------------------------------------//
void Board::initBoard(const string& fileName)
{
	clearBoard();
	FoodPlaces.clear();
	
	ifstream file;
	file.open(fileName);

	PlayWithBoard(file);

	checkException(fileName);

	file.close();
}
//-----------------------------------------------------------------------------------------------//
void Board::PlayWithBoard(ifstream& file)
{
	file.seekg(0, std::ios::end);
	long end = static_cast<long>(file.tellg()); // size of the file
	file.seekg(0, std::ios::beg);

	int count = 0;
	int col = 0, legendAppeared = 0;
	char lastChar = 'a'; // just a default, not important what
	int beyondFirstLine = 0;

	while (count < end)
	{
		unsigned char character = file.get();

		if (beyondFirstLine != 0 && col >= COLS) // if the line is over the first line of the board
		{
			while (character != '\n' && count <= end)
			{
				count++;
				character = file.get();
			}
			if (count <= end)
			{
				ROWS++;
			}
			count += 2;
			col = 0;
		}
		else
		{
			if (character == WALL)
			{
				board[ROWS][col] = WALL;
			}
			else if (character == GHOST)
			{
				// % 4 is necessary if ghostCounter > 4 then we will run over the first ghosts to enter
				charactersLoc[(ghostCounter % 4) + 1].set_X(col); // update the ghost`s location
				charactersLoc[(ghostCounter % 4) + 1].set_Y(ROWS);
				ghostCounter++;
				board[ROWS][col] = WHITE_SPACE;
			}
			else if (character == PACMAN)
			{
				charactersLoc[0].set_X(col); // update pacman`s lcoation
				charactersLoc[0].set_Y(ROWS);
				board[ROWS][col] = WHITE_SPACE;
				pacmanCount++;
			}
			else if (character == EMPTY_CELL)
			{
				board[ROWS][col] = WHITE_SPACE;
			}
			else if (character == WHITE_SPACE)
			{
				TotalScore++;
				character = BREADCRUMBS;
				board[ROWS][col] = character;
			}
			else if (character == LEGEND)
			{
				if (beyondFirstLine != 0 && col + LEGENDCOLS > COLS) // the legend is out of bound
				{
					exceptionBoard.setMessage("The legend is out of bounds.");
				}
				 
				legend.set_X(col);
				legend.set_Y(ROWS);
				board[ROWS][col] = WHITE_SPACE;
				legendAppeared = 1;
				legendCount++;
			}
			else if (character == '\n' || count + 1 == end)
			{
				if (beyondFirstLine == 0) // if we in the first line
				{
					if (col >= MaxCols)
					{
						exceptionBoard.setMessage("The first line is out of bounds.");
					}
					else if (legendAppeared == 1 && MaxCols - legend.get_X() < 20) // if the legend appeared && no enough space for the legend
					{
						exceptionBoard.setMessage("The legend is out of bounds.");
					}
					if (legendAppeared == 1 && legend.get_X() + 19 > COLS) // if the legend is in the end of the line
					{
						COLS = legend.get_X() + 19; //set the new line to be in the size of the legend
					}
				}
				if (beyondFirstLine != 0 && col < COLS) // if the line is shorter then the first line
				{
					insertFullLine(col);
					col = 0;
				}
				else
				{
					beyondFirstLine = 1;
					col = 0;
				}
				count++;
				ROWS++;

			}
			else // if its a non-valid key
			{
				board[ROWS][col] = WHITE_SPACE; // as a default - we use it as %
				count++;
			}

			if (count + 1 == end && col + 1 < COLS) // if we are in the last character but the line is shorter then the first 
			{
				insertFullLine(col + 1);
			}
			if (beyondFirstLine == 0)
			{
				COLS++;
			}
			if (character != '\n')
			{
				col++;
				lastChar = character;
			}
			count++;

		}

	}

	if (ghostCounter > MaxCharacters - 1) // ghosts > 4 
	{
		ghostCounter = 4;
	}


	makeATunnel();
	makeALegend();
	pointsOfBreadscrumbs();

}
//-----------------------------------------------------------------------------------------------//
void Board::pointsOfBreadscrumbs()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (board[i][j] == BREADCRUMBS)
			{
				Point temp(j, i);
				FoodPlaces.push_back(temp);
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------//
void Board::checkException(const string& fileName)
{
	if (ROWS > MaxRows || ROWS == 0 || COLS > MaxCols || COLS == 0)
	{
		exceptionBoard.setMessage("The size of the board exceeds the maximum dimensions (80X25).");
	}
	if (legendCount == 0)
	{
		exceptionBoard.setMessage("No Legend character inserted.");
	}
	if (pacmanCount == 0)
	{
		exceptionBoard.setMessage("No Pacman character inserted.");
	}
	
	for (unsigned int i = 0; i < ghostCounter + pacmanCount; i++) // check if the init position for the creatures is in the frame of the board
	{
		if (charactersLoc[i].get_X() == 0 || charactersLoc[i].get_X() + 1 == COLS || charactersLoc[i].get_Y() == 0 || charactersLoc[i].get_Y() + 1 == ROWS)
		{
			if (i == 0)
				exceptionBoard.setMessage("The pacman is in the tunnel - Invalid initiliaze location");
			else
			{
				exceptionBoard.setMessage(string("Ghost ") + string(std::to_string(i)) + string(" is in the tunnel - Invalid initiliaze location"));
			}
		}
	}

	if (exceptionBoard.getSize() > 0)
	{
		exceptionBoard.setScreenName(fileName);
		throw exceptionBoard;
	}
}
//-----------------------------------------------------------------------------------------------//
void Board::insertFullLine(int col)
{
	while (col < COLS)
	{
		board[ROWS][col] = WHITE_SPACE;
		col++;

	}
}
//-----------------------------------------------------------------------------------------------//
void Board::makeATunnel()
{
	for (int i = 0; i < ROWS; i++)
	{
		if (board[i][0] == BREADCRUMBS) // if there is a BREADSCRUMB on the frame
		{
			TotalScore--;
			board[i][0] = WHITE_SPACE;
		}
		if (board[i][COLS - 1] == BREADCRUMBS)
		{
			board[i][COLS - 1] = WHITE_SPACE;
			TotalScore--;
		}

		
	}
	for (int i = 0; i < COLS; i++)
	{
		if (board[0][i] == BREADCRUMBS)
		{
			TotalScore--;
			board[0][i] = WHITE_SPACE;
		}
		if (board[ROWS][i] == BREADCRUMBS)
		{
			TotalScore--;
			board[ROWS][i] = WHITE_SPACE;
		}
	}

}
//-----------------------------------------------------------------------------------------------//
void Board::makeALegend()
{
	if (legend.get_Y() + 1 == ROWS) // if the legend is the last line
	{
		ROWS += 2;
	}
	else
	{
		ROWS++;
	}

	for (int i = 0; i < LEGENDROWS; i++)
	{
		for (int j = 0; j < LEGENDCOLS; j++)
		{
			if (board[legend.get_Y() + i][legend.get_X() + j] == BREADCRUMBS)
			{
				TotalScore--;
			}
			board[legend.get_Y() + i][legend.get_X() + j] = WHITE_SPACE; // init the legend places into space
		}

		if (legend.get_Y() + i >= ROWS)
		{
			ROWS++;
		}
	}
}
//-----------------------------------------------------------------------------------------------//
void Board::printCell(int x, int y) const
{
	
	gotoxy(x, y);
	cout << board[y][x];
}
//-----------------------------------------------------------------------------------------------//
void Board::printBoard(bool gameColor) const
{
	gotoxy(0, 0);

	int i, j;

	if (gameColor)
	{
		setTextColor(Colors::WHITE);
	}


	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if (board[i][j] == WALL && gameColor)
			{
				setTextColor(wallColor);
			}

			cout << board[i][j];

			if (gameColor)
			{
				setTextColor(Colors::WHITE);
			}
		}

		cout << endl;

	}
}
//-----------------------------------------------------------------------------------------------//
bool Board::isValidMove(const Point& cell) const
{
	unsigned char typeChar = board[cell.get_Y()][cell.get_X()]; // get board char for the next move

	// If cell is out of limit or a tunnel
	if (cell.get_X() <= 0 || cell.get_Y() <= 0 || cell.get_Y() >= ROWS - 1 || cell.get_X() >= COLS - 1)
		return false;

	// If cell is a wall
	if (typeChar == Board::WALL)
	{
		return false;
	}

	// Otherwise
	return true;
}
//-----------------------------------------------------------------------------------------------//
