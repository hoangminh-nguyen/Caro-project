#include "_Game.h"

void main() {
	_Common::fixConsoleWindow();
	SetConsoleTitle(L"CARO");
	_Game g;
	//g.loadFile("taiminh.txt");
	g.showMenu();
	//g.playGame();

	//for (int i = 0; i < 255; i++)
	//{
	//	_Common::setTextColor(i);
	//	cout << i << " hello" << endl;
	//}

	//play game
	//g.startGame();
	//
	//while (g.isContinue()) { 
	//	g.waitKeyBoard();
	//	if (g.getCommand() == 27) {
	//		g.exitGame();
	//	}
	//	if (g.getCommand() == 'L') {
	//		g.saveGame();
	//	}
	//	else {
	//		switch (g.getCommand()) {
	//		case 'A':
	//			g.moveLeft();
	//			break;
	//		case 'W':
	//			g.moveUp();
	//			break;
	//		case 'S':
	//			g.moveDown();
	//			break;
	//		case 'D':
	//			g.moveRight();
	//			break;
	//		case 13: //enter
	//			if (g.processCheckBoard()) {
	//				switch (g.processFinish()) {
	//				case -1: 
	//				case 1: 
	//				case 0:
	//					if (g.askContinue() != 'Y') g.exitGame();
	//					else g.startGame();
	//				}
	//			}
	//			break;
	//		}
	//	}
	//}
	//return;
}