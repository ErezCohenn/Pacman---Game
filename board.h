#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Colors.h"
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include "io_utils.h"
#include "point.h"
#include <fstream>
#include <string>
#include <vector>
#include "ExceptionBoard.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

class Board
{
public:
	//-------------------------------------Enums---------------------------------------------------------//
	enum { BREADCRUMBS = 248, WALL = '#', WHITE_SPACE = 32, GHOST = '$', PACMAN = '@', EMPTY_CELL = '%', LEGEND = '&' };
	enum { LEGENDROWS = 3, LEGENDCOLS = 20 };
	enum { MaxRows = 25, MaxCols = 80, MaxCharacters = 5 };

private:
	//-----------------------------------------Data Members----------------------------------------------//
	Colors wallColor;
	Point legend;
	ExceptionBoard exceptionBoard;
	vector<Point> FoodPlaces;
	unsigned char board[MaxRows][MaxCols] = { WHITE_SPACE };
	int TotalScore, ROWS, COLS;
	Point charactersLoc[MaxCharacters];
	unsigned int pacmanCount = 0, legendCount = 0, ghostCounter = 0;

	//-----------------------------------Private Member Functions-----------------------------------------//
	void PlayWithBoard(ifstream& file);
	void makeALegend();
	void insertFullLine(int col); //insert whitespaces when a line is shorter then the first line
	void clearBoard();
	void makeATunnel();
	void pointsOfBreadscrumbs();
	void checkException(const string& fileName);

public:
	//-----------------------------------Public Member Functions-----------------------------------------//
	Board() : TotalScore(0), wallColor(Colors::LIGHTMAGENTA), ROWS(0), COLS(0), FoodPlaces(0) {}//ctor

	void initBoard(const string& fileName);
	void printCell(int x, int y) const;
	void printBoard(bool gameColor) const;
	bool isValidMove(const Point& cell) const;

	//--------------------------------------Get Functions------------------------------------------------//
	unsigned char getCellVal(int row, int col) const;
	const Point& getLocation(int ind) const { return charactersLoc[ind]; }
	int getTotalScore() const { return TotalScore; }
	int getGhostCounter() const { return ghostCounter; }
	int getLegend_x() const { return legend.get_X(); }
	int getLegend_y() const { return legend.get_Y(); }
	unsigned int getLineLen() const { return COLS; }
	unsigned int getRowNumber() const { return ROWS; }
	Colors getWallColor() const { return wallColor; }
	size_t getOptionalIndex() const { return FoodPlaces.size(); }
	const Point& getAPointForFruit(int num) const { return FoodPlaces[num]; }

	//--------------------------------------Set Functions-----------------------------------------------//
	void setCellVal(int row, int col, unsigned char ch);
	void setTotalScore() { TotalScore--; }
	void setWallColor(Colors color) { wallColor = color; }
};

