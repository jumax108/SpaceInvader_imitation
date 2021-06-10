#include <Windows.h>
#include <stdio.h>

#include "User.h"
#include "Queue.h"
#include "ScreenBuffer.h"
#include "InputManager.h"
#include "GameScene.h"
#include "Bullet.h"
#include "GameOverScene.h"

void CUser::update() {

	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;

	while (keyboardQue->isEmpty() == false) {
		int msg;
 		keyboardQue->pop(&msg);

		switch (msg) {
		case VK_ESCAPE:
			((CGameScene*)scene)->_menuMode = true;
			scene->_ignoreKeyPressing = true;
			break;
		case VK_LEFT:
			if (_pos.x > 1) {
				_pos.x -= 1;
			}
			break;
		case VK_RIGHT:
			if (_pos.x + _width < (int)SCREEN_BUFFER_INFO::width) {
				_pos.x += 1;
			}
			break;
		case VK_SPACE:
			// น฿ป็
			((CGameScene*)scene)->_unit.push_back((CBaseObject*)new CBullet(_pos.x + 2, _pos.y));

			break;
#ifdef CHEAT
		case 'R':

			_immortal = !_immortal;

			break;
		case 'P':
			for (int colCnt = 1; colCnt < (int)SCREEN_BUFFER_INFO::width - 3; ++colCnt) {
				((CGameScene*)scene)->_unit.push_back((CBaseObject*)new CBullet(colCnt, _pos.y));
			}
			break;
#endif
		}

		
	}

}

void CUser::render() {

	for (int positionCnt = 0; positionCnt < _patternPosNum; ++positionCnt) {

		position* ptrPosition = &_patternPos[positionCnt];

		CScreenBuffer::getInstance()->drawText(_pos.x + ptrPosition->x, _pos.y + ptrPosition->y, _pattern);

	}

	CScreenBuffer::getInstance()->drawText(2, 1, "Life: ");
	CScreenBuffer::getInstance()->drawText(8, 1, _hp + '0');

#ifdef CHEAT

	CScreenBuffer::getInstance()->drawText(2, 2, "IMMORTAL: ");
	CScreenBuffer::getInstance()->drawText(15, 2, _immortal ? "true":"false");

#endif

}

void CUser::OnCollision(CBaseObject* otherObj) {

#ifdef CHEAT

	if (_immortal == true) {
		return;
	}

#endif

	if (strcmp(((CUnit*)otherObj)->_tag, "enemy_bullet") == 0) {

		_hp -= 1;

		if (_hp == 0) {

			nextScene = (CScene*)new CGameOverScene();

		}

	}

}


CUser::CUser() {

#ifdef CHEAT

	_immortal = false;

#endif

	_tag = (char*)"user";
	_isDead = false;

	_pos.x = (int)SCREEN_BUFFER_INFO::width / 2 - 2;
	_pos.y = 25;
	_width = 5;

	_hp = 3;


	FILE* userData;
	fopen_s(&userData, "data/user", "rb");

	fseek(userData, 0, SEEK_END);
	int fileSize = ftell(userData);
	rewind(userData);

	fread(&_pattern, sizeof(_pattern), 1, userData);
	fread(&_patternPosNum, sizeof(_patternPosNum), 1, userData);
	fread(_patternPos, sizeof(CUnit::position::dataType), _patternPosNum * 2, userData);

	fclose(userData);

	/*
	_pattern = 'O';
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
	*/
}