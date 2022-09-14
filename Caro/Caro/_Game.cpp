#include "_Game.h"

_Game::_Game()
{
	_b = new _Board();
	_loop = _turn = true;
	_command = -1; 
	_x = BoardLeft; _y = BoardTop;
	countX = countO = 0;
}

_Game::~_Game()
{
	delete _b;
}

int _Game::getCommand()
{
	return _command;
}

bool _Game::isContinue()
{
	return _loop;
}

char _Game::waitKeyBoard()
{
	_command = toupper(_getch());
	return _command;
}

char _Game::askContinue()
{
	int boardSize = BoardSize;
	int left = BoardLeft;
	_Common::gotoXY(left, _b->getYAt(boardSize - 1, 0) + 6);
	_Common::setTextColor(WHITE);
	cout << "PRESS ENTER TO PLAY AGAIN";
	return waitKeyBoard();

}

void _Game::startGame()
{
	system("cls");
	delete _b;
	_b = new _Board();
	_b->resetData(); // Setting the original data
	_b->drawBoard(); // Draw boad
	countX = countO = 0;
	_turn = true;
	_x = _b->getXAt(_b->getSize() / 2, _b->getSize() / 2);
	_y = _b->getYAt(_b->getSize() / 2, _b->getSize() / 2);
	_Common::gotoXY(_x, _y);
	drawTitle();
	showInstruction();
	showGameTrack();
	playGame();
}

void _Game::playGame()
{
	while (isContinue()) {
		waitKeyBoard();
		if (getCommand() == 27) {
			return;
		}
		if (getCommand() == 'L') {
			saveGame();
		}
		else {
			switch (getCommand()) {
			case 'A':
				moveLeft();
				break;
			case 'W':
				moveUp();
				break;
			case 'S':
				moveDown();
				break;
			case 'D':
				moveRight();
				break;
			case 13: //enter
				if (processCheckBoard()) {

					showGameTrack();
					switch (processFinish()) {
					case -1: //X win
						showWinEffect();
						if (askContinue() != 13) return;
						else {
							startGame();
							return;
						};
						break;
					case 1: //O win
						showWinEffect();
						if (askContinue() != 13) return;
						else {
							startGame();
							return;
						};
						break;
					case 0: // Draw
						showDrawEffect();
						if (askContinue() != 13) return;
						else {
							startGame();
							return;
						};
						break;
					}

					showGameTrack();
				}
				break;
			}
		}
	}
}

void _Game::exitGame()
{
	system("cls");
	_loop = false;
}

void _Game::saveGame()
{
	clearSaveScreen();
	int left = BoardLeft;
	_Common::gotoXY(left, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	string fileName;
	string fileNameSub;
	int i = 1;
	cout << "Input file name: ";
	getline(cin, fileName);
	while (fileName == "") getline(cin, fileName);
	fileNameSub = fileName;
	while (isExist(fileNameSub)) {
		fileNameSub = fileName + "(" + to_string(i) + ")";
		i++;
	}
	_Common::gotoXY(left, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 5);
	cout << "File saved as name: " << fileNameSub << endl;
	saveFile(fileNameSub);
	_Common::gotoXY(_x, _y);
}

void _Game::clearSaveScreen()
{
	int left = BoardLeft;
	_Common::gotoXY(left, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	_Common::setTextColor(WHITE);
	cout << "                                         " << endl;
	cout << "                                         " << endl;
	cout << "                                         " << endl;
}

bool _Game::isExist(string fileName)
{
	fstream fin;
	fin.open(fileName + ".txt", fstream::in);
	if (fin.is_open()) {
		fin.close();
		return true;
	}
	else return false;
}

void _Game::saveFile(string fileName)
{
	ofstream fout;
	fout.open(fileName + ".txt", fstream::out);
	if (fout.fail()) {
		cout << "Khong mo dc file!" << endl;
		fout.close();
		return;
	}
	fout << _b->getSize() << " " << _b->getLeft() << " " << _b->getTop() << endl;
	fout << _turn << " " << countX << " " << countO << endl;
	for (int i = 0; i < _b->getSize(); i++) {
		for (int j = 0; j < _b->getSize(); j++) {
			fout << _b->getPArr()[i][j].getCheck();
			if (j == _b->getSize() - 1) fout << endl;
			else fout << " ";
		}
	}
	fout.close();
}

void _Game::loadGame()
{
	vector<string> savedFiles = getSavedFileName();
	system("cls");
	drawTitle();
	drawSavedFileOption(uiTop + 9, uiLeft, savedFiles);
	int choose = 0;
	setSavedFileOption(uiTop, uiLeft, choose, savedFiles);
	while (true) {
		waitKeyBoard();
		if (_command == 13) {
			//BACK
			if (choose == savedFiles.size())
				return;
			loadFile(savedFiles[choose]);
			playGame();
			return;
		}
		else {
			switch (_command) {
			case 'W':
				if (choose == 0) break;
				choose--;
				setSavedFileOption(uiTop, uiLeft, choose, savedFiles);
				break;
			case 'S':
				if (choose == savedFiles.size()) break;
				choose++;
				setSavedFileOption(uiTop, uiLeft, choose, savedFiles);
				break;
			}
		}
	}

}

void _Game::drawSavedFileOption(int top, int left, vector<string> savedFiles)
{
	_Common::setTextColor(GRAY);
	for (int i = 0; i < savedFiles.size(); i++)
	{
		_Common::gotoXY(left - 3, top);
		cout << "   " << savedFiles[i].substr(0, savedFiles[i].size() - 4);
		top += 2;
	}
	_Common::gotoXY(left - 3, top);
	cout << "   BACK";
}

void _Game::setSavedFileOption(int top, int left, int choose, vector<string> savedFiles)
{
	drawSavedFileOption(top + 9, left, savedFiles);
	int curTop = top + 9 + 2 * choose;
	_Common::gotoXY(left - 3, curTop);
	_Common::setTextColor(YELLOW);
	cout << (char)16;
	_Common::gotoXY(left, curTop);
	_Common::setTextColor(WHITE);
	if (choose == savedFiles.size()) cout << "BACK";
	else cout << savedFiles[choose].substr(0, savedFiles[choose].size() - 4);
}

void _Game::loadFile(string fileName)
{
	ifstream fin;
	fin.open(fileName, fstream::in);
	if (fin.fail()) {
		cout << "Khong mo dc file!" << endl;
		fin.close();
		return;
	}
	int size, left, top, turn;
	fin >> size >> left >> top;
	fin >> turn >> countX >> countO;
	preX = preY = 0;
	_turn = (turn == 1);
	_loop = true;
	_b = new _Board();
	_b->resetData();
	int check;
	for (int i = 0; i < _b->getSize(); i++) {
		for (int j = 0; j < _b->getSize(); j++) {
			fin >> check;
			_b->setPArrCheck(i, j, check);
		}
	}
	fin.close();
	system("cls");
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
	_b->drawBoard();
	_b->displayUI();
	_Common::gotoXY(_x, _y);
	drawTitle();
	showInstruction();
	showGameTrack();
}

vector<string> _Game::getSavedFileName()
{
	vector<string> savedFiles;
	path path = current_path();
	for (const auto& entry : directory_iterator(path)) {
		if (entry.path().filename().string().ends_with(".txt")) {
			savedFiles.push_back(entry.path().filename().string());
		}
	}
	return savedFiles;
}

void _Game::showMenu()
{
	system("cls");
	drawTitle();
	drawMenuOption(uiTop + 9, uiLeft);
	int choose = 0;
	setMenuOption(uiTop, uiLeft, choose);
	while (true) {
		waitKeyBoard();
		if (_command == 13) {
			switch (choose) {
			case 0:
				startGame(); //2 player
				break;
			case 1:
				//play with computer
				break;
			case 2:
				loadGame(); //load game
				break;
			case 3:
				exitGame(); //exit
				return;
			}

			//ve lai menu
			system("cls");
			drawTitle();
			drawMenuOption(uiTop + 9, uiLeft);
			choose = 0;
			setMenuOption(uiTop, uiLeft, choose);
		}
		else {
			switch (_command) {
			case 'W':
				if (choose == 0) break;
				choose--;
				setMenuOption(uiTop, uiLeft, choose);
				break;
			case 'S':
				if (choose == 3) break;
				choose++;
				setMenuOption(uiTop, uiLeft, choose);
				break;
			}
		}
	}
}

void _Game::drawTitle()
{
	int width = 18;
	int height = 6;
	for (int i = 0; i <= width; i++)
	{
		if (i < 4) _Common::setTextColor(RED);
		else if (i < 9) _Common::setTextColor(BLUE);
		else if (i < 14) _Common::setTextColor(GREEN);
		else _Common::setTextColor(YELLOW);
		for (int j = 0; j < height; j++) {
			if (i == 0 || i == 10 || i == 15 || i == 18) {
			}
			else if (i == 4 || i == 9 || i == 14) continue;
			else if (i == 1 || i == 2 || i == 3 || i == 16 || i == 17) {
				if (j != 0 && j != height - 1) continue;
			}
			else if (i == 5 || i == 8) {
				if (j == 0) continue;
			}
			else if (i == 6 || i == 7 || i == 11 || i == 12) {
				if (j != 0 && j != height - 3) continue;
			}
			else if (i == 13) {
				if (j == height - 3) continue;
			}
			_Common::gotoXY(i + uiLeft, j + uiTop);
			cout << (char)219;
		}
	}
}

void _Game::drawMenuOption(int top, int left)
{
	_Common::setTextColor(GRAY);
	_Common::gotoXY(left - 3, top++);
	cout << "   2 PLAYER";
	_Common::gotoXY(left - 3, (++top)++);
	cout << "   PLAY WITH COMPUTER";
	_Common::gotoXY(left - 3, (++top)++);
	cout << "   LOAD GAME";
	_Common::gotoXY(left - 3, ++top);
	cout << "   EXIT";
}

void _Game::setMenuOption(int top, int left, int choose)
{
	drawMenuOption(top + 9, left);
	int curTop = top + 9 + 2 * choose;
	_Common::gotoXY(left - 3, curTop);
	_Common::setTextColor(YELLOW);
	cout << (char)16;
	_Common::gotoXY(left, curTop);
	_Common::setTextColor(WHITE);
	if (choose == 0) cout << "2 PLAYER";
	else if (choose == 1) cout << "PLAY WITH COMPUTER";
	else if (choose == 2) cout << "LOAD GAME";
	else if (choose == 3) cout << "EXIT";
}

void _Game::showInstruction()
{
	vector<string> instruction{ "W,A,S,D - MOVE", "Enter   - SELECT", "L       - SAVE GAME", "ESC     - BACK TO MENU" };
	int top = 11, left = 100;
	_Common::setTextColor(WHITE);
	for (int i = 0; i < instruction.size(); i++)
	{
		_Common::gotoXY(left, top);
		cout << instruction[i];
		top += 1;
	}
}

void _Game::showGameTrack()
{
	_Common::gotoXY(5, 11);
	if (_turn) {
		_Common::setTextColor(RED);
		cout << "TURN X";
	}
	else
	{
		_Common::setTextColor(BLUE);
		cout << "TURN O";
	}
	_Common::setTextColor(WHITE);
	_Common::gotoXY(5, 14);
	cout << "X: " << countX << "   ";
	_Common::gotoXY(5, 16);
	cout << "O: " << countO << "   ";
	_Common::gotoXY(_x, _y);
}

void _Game::showWinEffect()
{
	Sleep(500);
	int boardSize = BoardSize;
	int left = BoardLeft;
	string blank = "";
	string roll;
	if (_turn) {
		_Common::setTextColor(RED);
		blank += "-- X WIN --";
		roll = " X ";
	}
	else {
		_Common::setTextColor(BLUE);
		blank += "-- O WIN --";
		roll = " O ";
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			_Common::gotoXY(_b->getXAt(i, j) -1, _b->getYAt(i, j));
			cout << roll;
			Sleep(10);
		}
	}
	for (int i = 0; i < 45; i++)
	{
		_Common::setTextColor(i%15);
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				_Common::gotoXY(_b->getXAt(i, j) - 1, _b->getYAt(i, j));
				cout << roll;
			}
		}
		Sleep(30);
	}
	if (_turn) _Common::setTextColor(RED);
	else _Common::setTextColor(BLUE);
	for (int i = 0; i < boardSize*4 - 11; i++)
	{
		_Common::gotoXY(left, _b->getYAt(boardSize - 1, 0) + 4);
		cout << blank;
		blank = " " + blank;
		Sleep(40);
	}
}

void _Game::showDrawEffect()
{
	Sleep(500);
	int boardSize = BoardSize;
	int left = BoardLeft;
	string blank = "";
	string roll;
	_Common::setTextColor(WHITE);
	blank += "-- YOU BOTH DRAW --";
	roll = " - ";
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			_Common::gotoXY(_b->getXAt(i, j) - 1, _b->getYAt(i, j));
			cout << roll;
			Sleep(10);
		}
	}
	for (int i = 0; i < 45; i++)
	{
		_Common::setTextColor(i % 15);
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				_Common::gotoXY(_b->getXAt(i, j) - 1, _b->getYAt(i, j));
				cout << roll;
			}
		}
		Sleep(30);
	}
	_Common::setTextColor(YELLOW);
	for (int i = 0; i < boardSize * 4 - 11; i++)
	{
		_Common::gotoXY(left, _b->getYAt(boardSize - 1, 0) + 4);
		cout << blank;
		blank = " " + blank;
		Sleep(40);
	}
}

int _Game::processFinish()
{
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard();
	switch (pWhoWin) {
	case -1: //X win
		//printf("The player %d won and the player %d lost\n", true, false);
		break;
	case 1: // O win
		//printf("The player %d won and the player %d lost\n", false, true);
		break;
	case 0: //Draw
		//printf("The player %d draw with the player %d\n", false, true);
		break;
	case 2: //game continue
		_turn = !_turn;
	}
	_Common::gotoXY(_x, _y);// Return the current position of cursor
	return pWhoWin;
}

bool _Game::processCheckBoard()
{
	switch (_b->checkBoard(_x, _y, _turn)) {
	case -1:
		if (countX + countO > 0) checkBoardUI();
		_Common::gotoXY(_x - 1, _y);
		_Common::setTextColor(NEWX);
		printf(" X ");
		countX++;
		break;
	case 1:
		if (countX + countO > 0) checkBoardUI();
		_Common::gotoXY(_x - 1, _y);
		_Common::setTextColor(NEWO);
		printf(" O ");
		countO++;
		break;
	case 0: return false;
	}
	preX = _x;
	preY = _y;
	_Common::setTextColor(WHITE);
	return true;
}

void _Game::checkBoardUI()
{
	_Common::gotoXY(preX - 1, preY);
	if (_turn) {
		_Common::setTextColor(BLUE);
		cout << " O ";
	}
	else {
		_Common::setTextColor(RED);
		cout << " X ";
	}

	_Common::setTextColor(WHITE);
}

//move in game board
void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_x += 4;
		_Common::gotoXY(_x, _y);
	}

}
void _Game::moveLeft()
{
	if (_x > _b->getXAt(0, 0)) {
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}

}
void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0)) {
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}
