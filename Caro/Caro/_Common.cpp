#include "_Common.h"

void _Common::fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	GetWindowRect(consoleWindow, &r); 

	MoveWindow(consoleWindow, r.left, r.top, 1150, 1000, TRUE);
	//LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	//style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	//SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void _Common::gotoXY(int pX, int pY)
{
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void _Common::setTextColor(int color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
}
