#include "_Board.h"


_Board::_Board()
{
    _size = BoardSize;
    _left = BoardLeft;
    _top = BoardTop;
    _pArr = new _Point * [_size];
    for (int i = 0; i < _size; i++) _pArr[i] = new _Point[_size];
}

_Board::~_Board()
{
    for (int i = 0; i < _size; i++) delete[] _pArr[i];
    delete[] _pArr;
}


void _Board::setPArrCheck(int i, int j, int check)
{
    _pArr[i][j].setCheck(check);
}

void _Board::displayUI()
{
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            _Common::gotoXY(_pArr[i][j].getX(), _pArr[i][j].getY());
            if (_pArr[i][j].getCheck() == 0) continue;
            else if (_pArr[i][j].getCheck() == 1) {
                _Common::setTextColor(BLUE);
                cout << "O";
            }
            else if (_pArr[i][j].getCheck() == -1) {
                _Common::setTextColor(RED);
                cout << "X";
            }
        }
    }
    _Common::setTextColor(WHITE);
}


void _Board::resetData()
{
    if (_size == 0) return; 
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            _pArr[i][j].setX(4 * j + _left + 2);
            _pArr[i][j].setY(2 * i + _top + 1);
            _pArr[i][j].setCheck(0);
        }
    }
}

void _Board::drawBoard()
{
    _Common::setTextColor(WHITE);
    if (_pArr == NULL) return; 
    for (int i = 0; i <= _size; i++) {
        for (int j = 0; j <= _size; j++) {
            _Common::gotoXY(_left + 4 * i, _top + 2 * j);
            printf(".");
        }
    }
    _Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY());
}

int _Board::checkBoard(int pX, int pY, bool pTurn)
{
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0) {
                if (pTurn) _pArr[i][j].setCheck(-1);
                else _pArr[i][j].setCheck(1);
                return _pArr[i][j].getCheck();
            }
        }
    }
    return 0;
}

int _Board::testBoard()
{
    int countChecked = 0;
    int countXO[4] = { 0, 0, 0, 0 }; //X vertical, O vertical, X horizontal, O horizontal
    //check horizontal and vertical
    for (int i = 0; i < _size; i++) {
        countXO[0] = countXO[1] = countXO[2] = countXO[3] = 0;
        for (int j = 0; j < _size; j++) {
            int getBoxValueHorizontal = _pArr[i][j].getCheck();
            int getBoxValueVertical = _pArr[j][i].getCheck();
            if (getBoxValueHorizontal != 0) { countChecked++; }
            // check vertical row X and O
            switch (getBoxValueVertical) {
                case -1: {
                    countXO[1] = 0;
                    if (++countXO[0] == 5) { 
                        return -1; 
                    }
                    break;
                }
                case 1: {
                    countXO[0] = 0;
                    if (++countXO[1] == 5) { 
                        return 1; 
                    }
                    break;
                }
                case 0: {
                    countXO[1] = 0;
                    countXO[0] = 0;
                    break;
                }
            }
            // check horizontal row X and O
            switch (getBoxValueHorizontal) {
                case -1: {
                    countXO[3] = 0;
                    if (++countXO[2] == 5) { 
                        return -1; 
                    }
                    break;
                }
                case 1: {
                    countXO[2] = 0;
                    if (++countXO[3] == 5) { 
                        return 1; 
                    }
                    break;
                }
                case 0: {
                    countXO[3] = 0;
                    countXO[2] = 0;
                    break;
                }
            }
        }
    }

    if (countChecked == _size * _size) { return 0; }
    // check diagonal 

    int countXDiagonal[4] = { 0, 0, 0, 0 }; //LR upper, LR lower, RL upper, RL lower -- X
    int countODiagonal[4] = { 0, 0, 0, 0 }; //LR upper, LR lower, RL upper, RL lower -- O
    for (int i = 0; i < _size; i++) {
        countXDiagonal[0] = countXDiagonal[1] = countXDiagonal[2] = countXDiagonal[3] = 0;
        countODiagonal[0] = countODiagonal[1] = countODiagonal[2] = countXDiagonal[3] = 0;
        for (int j = 0; j < _size-i; j++) {
            int getBoxValueUpperLR = _pArr[j][j + i].getCheck();
            int getBoxValueLowerLR = _pArr[j + i][j].getCheck();
            int getBoxValueUpperRL = _pArr[_size - j - 1 - i][j].getCheck();
            int getBoxValueLowerRL = _pArr[j + i][_size - j - 1].getCheck();
            // check horizontal row X and O
            switch (getBoxValueUpperLR) {
            case -1: {
                countODiagonal[0] = 0;
                if (++countXDiagonal[0] == 5) { 
                    return -1; 
                }
                break;
            }
            case 1: {
                countXDiagonal[0] = 0;
                if (++countODiagonal[0] == 5) { 
                    return 1; 
                }
                break;
            }
            case 0: {
                countXDiagonal[0] = 0;
                countODiagonal[0] = 0;
                break;
            }
            }
            //
            switch (getBoxValueLowerLR) {
            case -1: {
                countODiagonal[1] = 0;
                if (++countXDiagonal[1] == 5) { 
                    return -1; 
                }
                break;
            }
            case 1: {
                countXDiagonal[1] = 0;
                if (++countODiagonal[1] == 5) { 
                    return 1; 
                }
                break;
            }
            case 0: {
                countODiagonal[1] = 0;
                countXDiagonal[1] = 0;
                break;
            }
            }
            //
            switch (getBoxValueUpperRL) {
            case -1: {
                countODiagonal[2] = 0;
                if (++countXDiagonal[2] == 5) { 
                    return -1; 
                }
                break;
            }
            case 1: {
                countXDiagonal[2] = 0;
                if (++countODiagonal[2] == 5) { 
                    return 1; 
                }
                break;
            }
            case 0: {
                countODiagonal[2] = 0;
                countXDiagonal[2] = 0;
                break;
            }
            }
            //
            switch (getBoxValueLowerRL) {
            case -1: {
                countODiagonal[3] = 0;
                if (++countXDiagonal[3] == 5) { 
                    return -1; 
                }
                break;
            }
            case 1: {
                countXDiagonal[3] = 0;
                if (++countODiagonal[3] == 5) { 
                    return 1; 
                }
                break;
            }
            case 0: {
                countODiagonal[3] = 0;
                countXDiagonal[3] = 0;
                break;
            }
            }
        }
    }
    return 2;
}

int _Board::getSize()
{
    return _size;
}

int _Board::getLeft()
{
    return _left;
}

int _Board::getTop()
{
    return _top;
}

int _Board::getXAt(int i, int j)
{
    return _pArr[i][j].getX();
}

int _Board::getYAt(int i, int j)
{
    return _pArr[i][j].getY();

}

_Point** _Board::getPArr()
{
    return _pArr;
}

