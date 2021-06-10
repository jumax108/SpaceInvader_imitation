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

	/* --------------------------------------------------------------------------- */
	/* 입력 처리 */
	/* --------------------------------------------------------------------------- */
	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;

	while (keyboardQue->isEmpty() == false) {
		int msg;
 		keyboardQue->pop(&msg);

		switch (msg) {
		case VK_ESCAPE:
			// 게임 메뉴 열기
			((CGameScene*)scene)->_isMenuMode = true;
			scene->_ignoreKeyPressing = true;
			break;
		case VK_LEFT:
			// 왼쪽으로 이동
			if (_pos.x > 1) {
				_pos.x -= 1;
			}
			break;
		case VK_RIGHT:
			// 오른쪽으로 이동
			if (_pos.x + _width < (int)SCREEN_BUFFER_INFO::width) {
				_pos.x += 1;
			}
			break;
		case VK_SPACE:
			// 공격
			((CGameScene*)scene)->_unit.push_back((CBaseObject*)new CBullet(_pos.x + 2, _pos.y));

			break;
#ifdef CHEAT
		case 'R':
			// 무적 모드 On/Off
			_immortal = !_immortal;

			break;
		case 'P':
			// 전체 화면 공격
			for (int colCnt = 1; colCnt < (int)SCREEN_BUFFER_INFO::width - 3; ++colCnt) {
				((CGameScene*)scene)->_unit.push_back((CBaseObject*)new CBullet(colCnt, _pos.y));
			}
			break;
#endif
		}

		
	}

}

void CUser::render() {


	/* --------------------------------------------------------------------------- */
	/* user 캐릭터 출력 */
	/* --------------------------------------------------------------------------- */
	for (int positionCnt = 0; positionCnt < _patternPosNum; ++positionCnt) {

		position* ptrPosition = &_patternPos[positionCnt];

		CScreenBuffer::getInstance()->drawText(_pos.x + ptrPosition->x, _pos.y + ptrPosition->y, _pattern);

	}

	/* --------------------------------------------------------------------------- */
	/* 목숨 표시 */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawText(2, 1, "Life: ");
	CScreenBuffer::getInstance()->drawText(8, 1, _hp + '0');

#ifdef CHEAT

	/* --------------------------------------------------------------------------- */
	/* 무적 상태 표시 */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawText(2, 2, "IMMORTAL: ");
	CScreenBuffer::getInstance()->drawText(15, 2, _immortal ? "true":"false");

#endif

}

void CUser::OnCollision(CBaseObject* otherObj) {

#ifdef CHEAT

	/* --------------------------------------------------------------------------- */
	/* 무적 모드 활성화 시, 총알과 충돌 처리하지 않음 */
	/* --------------------------------------------------------------------------- */
	if (_immortal == true) {
		return;
	}

#endif

	/* --------------------------------------------------------------------------- */
	/* 적군 총알 충돌 처리 */
	/* --------------------------------------------------------------------------- */
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


	/* --------------------------------------------------------------------------- */
	/* 유저 스프라이트 데이터 로딩 */
	/* --------------------------------------------------------------------------- */
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