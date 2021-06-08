#include <Windows.h>

#include "User.h"
#include "Queue.h"
#include "ScreenBuffer.h"
#include "InputManager.h"
#include "GameScene.h"

void CUser::update() {

	CQueue* keyboardQue = CInputManager::getInstance()->_keyboardQue;

	while (keyboardQue->isEmpty() == false) {
		int msg;
		keyboardQue->pop(&msg);

		switch (msg) {
		case VK_ESCAPE:
			((CGameScene*)scene)->_menuMode = true;
			break;
		case VK_LEFT:
			if (_x > 1) {
				_x -= 1;
			}
			break;
		case VK_RIGHT:
			if (_x + _width < (int)SCREEN_BUFFER_INFO::width) {
				_x += 1;
			}
			break;
		}

		
	}

}

void CUser::render() {

	for (int positionCnt = 0; positionCnt < _positionNum; ++positionCnt) {

		position* ptrPosition = &_position[positionCnt];

		CScreenBuffer::getInstance()->drawText(_x + ptrPosition->x, _y + ptrPosition->y, _pattern);

	}
}

CUser::CUser() {

	_x = (int)SCREEN_BUFFER_INFO::width / 2 - 2;
	_y = 25;
	_width = 5;

	_pattern = 'O';
	_positionNum = 11;

	_position[0].x = 0;
	_position[0].y = 1;

	_position[1].x = 0;
	_position[1].y = 2;

	_position[2].x = 0;
	_position[2].y = 3;

	_position[3].x = 2;
	_position[3].y = 0;

	_position[4].x = 2;
	_position[4].y = 1;

	_position[5].x = 2;
	_position[5].y = 2;

	_position[6].x = 1;
	_position[6].y = 2;

	_position[7].x = 3;
	_position[7].y = 2;

	_position[8].x = 4;
	_position[8].y = 1;

	_position[9].x = 4;
	_position[9].y = 2;

	_position[10].x = 4;
	_position[10].y = 3;
}