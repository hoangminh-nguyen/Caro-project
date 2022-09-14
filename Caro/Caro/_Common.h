#pragma once
#include <iostream>
#include <Windows.h>

#define RED 12
#define GREEN 10
#define BLUE 9
#define YELLOW 14
#define WHITE 15
#define GRAY 8
#define NEWX 116
#define NEWO 113

using namespace std;

class _Common
{

public:
	static void fixConsoleWindow();
	static void gotoXY(int, int);
	static void setTextColor(int);
};

