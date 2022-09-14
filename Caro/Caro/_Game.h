#pragma once
#include "_Board.h"
#include <conio.h>
#include <fstream>
#include <iostream> 
#include <vector>
#include <string>
#include <filesystem>
using namespace std;
using namespace filesystem;
class _Game
{
	_Board* _b;
	int preX, preY;
	bool _turn;
	int _x, _y; 
	int _command;
	bool _loop;
	int countX, countO;
	int uiTop = 2;
	int uiLeft = 45;
public:
	_Game();
	~_Game();

	int getCommand();
	bool isContinue();
	char waitKeyBoard();
	char askContinue();

	void startGame();
	void playGame();
	void exitGame();

	int processFinish();
	bool processCheckBoard();
	void checkBoardUI();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	//save file
	void saveGame();
	void clearSaveScreen();
	bool isExist(string fileName);
	void saveFile(string fileName);

	//load file
	void loadGame();
	void loadFile(string fileName);
	void drawSavedFileOption(int top, int left, vector<string> savedFiles);
	void setSavedFileOption(int top, int left, int choose, vector<string> savedFiles);
	vector<string> getSavedFileName();

	// show menu
	void showMenu();
	void drawTitle();
	void drawMenuOption(int top, int left);
	void setMenuOption(int top, int left, int choose);

	//game info
	void showInstruction();
	void showGameTrack();

	//winning effect
	void showWinEffect();
	void showDrawEffect();
};

