#include "Enemy.h"

#include "ScreenBuffer.h"

void CEnemy::update() {



}

void CEnemy::render() {

	for (int positionCnt = 0; positionCnt < _positionNum; ++positionCnt) {

		position* ptrPosition = &_position[positionCnt];

		CScreenBuffer::getInstance()->drawText(_x + ptrPosition->x, _y + ptrPosition->y, _pattern);

	}
}

CEnemy::CEnemy(int x , int y) {

	_x = x;
	_y = y;

	_pattern = '@';
	_positionNum = 4;

	_position[0].x = 0;
	_position[0].y = 0;

	_position[1].x = 1;
	_position[1].y = 0;

	_position[2].x = 2;
	_position[2].y = 0;

	_position[3].x = 1;
	_position[3].y = 1;

}