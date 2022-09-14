#pragma once
#include "_Point.h"
#include "_Common.h"
#include <string>
#define BoardSize 15;
#define BoardLeft 24;
#define BoardTop 11;

class _Board
{
private:
	int _size;
	int _left, _top;
	_Point** _pArr;
public:
	_Board();
	~_Board();

	//load board
	void setPArrCheck(int i, int j, int check);
	void displayUI();

	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	int testBoard();

	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);

	_Point** getPArr();


};

