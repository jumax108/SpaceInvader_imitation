#include <string.h>
#include <stdio.h>

#include "Queue.h"
#include "GameScene.h"
#include "User.h"
#include "Enemy.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "Bullet.h"
#include "ClearScene.h"
#include "ScreenBuffer.h"

constexpr int menuBoxWidth = 14;
constexpr int menuBoxHeight = 3;
constexpr int menuBoxX = (int)SCREEN_BUFFER_INFO::width / 2 - menuBoxWidth / 2;
constexpr int menuBoxY = (int)SCREEN_BUFFER_INFO::height - menuBoxHeight - 4;

void CGameScene::init() {

	/* --------------------------------------------------------------------------- */
	/* 적군 진행 방향 */
	/* --------------------------------------------------------------------------- */
	_enemyDirection = -1;


	/* --------------------------------------------------------------------------- */
	/* 스테이지 로딩 시, clear해서 이전 스테이지 데이터 제거 */
	/* --------------------------------------------------------------------------- */
	_unit.clear();

	/* --------------------------------------------------------------------------- */
	/* 유저 캐릭터 추가 */
	/* --------------------------------------------------------------------------- */
	_unit.push_back((CBaseObject*)new CUser());

	/* --------------------------------------------------------------------------- */
	/* 스테이지 데이터 (적군 위치) 로딩 */
	/* --------------------------------------------------------------------------- */
	FILE* stageData;
	char fileName[255] = {0,};
	sprintf_s(fileName, "data/stage%d", _stage);
	fopen_s(&stageData, fileName, "rb");

	fseek(stageData, 0, SEEK_END);
	int fileSize = ftell(stageData);
	rewind(stageData);

	fread(&_enemyNum, sizeof(_enemyNum), 1, stageData);
	for (int enemyCnt = 0; enemyCnt < _enemyNum ; enemyCnt++) {

		CUnit::position pos;
		fread(&pos, sizeof(CUnit::position), 1, stageData);
		_unit.push_back((CBaseObject*)new CEnemy(pos.x, pos.y));
	}

	fclose(stageData);
}

/* --------------------------------------------------------------------------- */
/* 게임 화면의 끝까지 갔는지 확인 후 처리*/
/* --------------------------------------------------------------------------- */
void CGameScene::checkWall() {

	for (CLinkedList<CBaseObject*>::iterator unitIter = _unit.begin(); unitIter != _unit.end(); ++unitIter) {

		CUnit* unit = (CUnit*)(*unitIter);

		if (unit == nullptr) {
			continue;
		}


		/* --------------------------------------------------------------------------- */
		/* 적군이 화면 끝으로 이동하면 방향 전환 */
		/* --------------------------------------------------------------------------- */
		if (strcmp(unit->_tag, "enemy") == 0) {
			for (int positionCnt = 0; positionCnt < unit->getPatternPositionNum(); ++positionCnt) {

				CUnit::position pos = unit->getPatternPosition(positionCnt);
				int width = unit->_width;
				CUnit::position::dataType x = unit->_pos.x;

				if (pos.x + x == 1) {
					_enemyDirection = 1;
				}
				else if (pos.x + width + x == (int)SCREEN_BUFFER_INFO::width - 3) {
					_enemyDirection = -1;
				}

			}
		}
		/* --------------------------------------------------------------------------- */
		/* 아군 총알이 화면 최상단으로 이동하면 제거 */
		/* --------------------------------------------------------------------------- */
		else if (strcmp(unit->_tag, "bullet") == 0) {

			if (unit->_pos.y == 1) {

				delete(unit);
				unit = nullptr;
				unitIter = _unit.erase(unitIter);
			}

		}
		/* --------------------------------------------------------------------------- */
		/* 적군 총알이 화면 최하단으로 이동하면 제거 */
		/* --------------------------------------------------------------------------- */
		else if (strcmp(unit->_tag, "enemy_bullet") == 0) {
			
			if (unit->_pos.y == ((int)SCREEN_BUFFER_INFO::height - 2)) {

				delete(unit);
				unit = nullptr;
				unitIter = _unit.erase(unitIter);
			}

		}

	}

}

void CGameScene::update() {

	/* --------------------------------------------------------------------------- */
	/* 키보드 입력 처리 */
	/* --------------------------------------------------------------------------- */
	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;


	/* --------------------------------------------------------------------------- */
	/* 인게임 메뉴가 켜져있는 상태 */
	/* --------------------------------------------------------------------------- */
	if (_isMenuMode == true) {
		while (keyboardQue->isEmpty() == false) {
			int msg;
			keyboardQue->pop(&msg);

			switch (msg) {
			case VK_ESCAPE:
				// ESC 누르면 게임 메뉴에서 탈출
				_isMenuMode = false;
				_ignoreKeyPressing = false;
				break;
			case VK_UP:
			case VK_DOWN:
				// UP, DOWN 시 선택된 메뉴 변경
				_menuIdx = 1 - _menuIdx;
				break;
			case VK_RETURN:
				// 메뉴 선택
				switch (_menuIdx) {
				case 0:
					// 게임 계속 진행하기
					_isMenuMode = false;
					_ignoreKeyPressing = false;
					break;
				case 1:
					// 타이틀 메뉴로 이동하기
					nextScene = (CScene*)new CTitleScene();
					break;
				}
				break;
			}

		}
	}
	/* --------------------------------------------------------------------------- */
	/* 인게임 메뉴가 꺼져있는 상태 */
	/* --------------------------------------------------------------------------- */
	else {

		/* --------------------------------------------------------------------------- */
		/* 모든 오브젝트 순회 */
		/* --------------------------------------------------------------------------- */
		for (CLinkedList<CBaseObject*>::iterator unitIter = _unit.begin(); unitIter != _unit.end(); ++unitIter) {
			
			if (*unitIter == nullptr) {
				continue;
			}

			/* --------------------------------------------------------------------------- */
			/* 사망 처리 된 오브젝트 제거 */
			/* --------------------------------------------------------------------------- */
			if (((CUnit*)(*unitIter))->_isDead == true) {
				delete(*unitIter);
				*unitIter = nullptr;
				unitIter = _unit.erase(unitIter);
				continue;
			}

			/* --------------------------------------------------------------------------- */
			/* 오브젝트 로직 처리 */
			/* --------------------------------------------------------------------------- */
			(*unitIter)->update();
		}
	}

	/* --------------------------------------------------------------------------- */
	/* 화면 끝까지 이동한 오브젝트 처리 */
	/* --------------------------------------------------------------------------- */
	checkWall();

	/* --------------------------------------------------------------------------- */
	/* 모든 오브젝트 충돌 처리, OnCollision 호출 */
	/* --------------------------------------------------------------------------- */
	checkCollision();


	/* --------------------------------------------------------------------------- */
	/* 모든 적군 사망 */
	/* --------------------------------------------------------------------------- */
	if (_enemyNum == 0) {

		/* --------------------------------------------------------------------------- */
		/* 게임 클리어 */
		/* --------------------------------------------------------------------------- */
		if (_stage == CGameScene::_stageNum) {

			nextScene = (CScene*)new CClearScene();

		}
		/* --------------------------------------------------------------------------- */
		/* 다음 스테이지 로딩 */
		/* --------------------------------------------------------------------------- */
		else {
			_stage += 1;
			init();
		}
	}

}

void CGameScene::render() {

	CScreenBuffer::getInstance()->clear();

	/* --------------------------------------------------------------------------- */
	/* 화면 외곽선 출력 */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);


	/* --------------------------------------------------------------------------- */
	/* 모든 오브젝트 render 호출 */
	/* --------------------------------------------------------------------------- */
	for (CLinkedList<CBaseObject*>::iterator unitIter = _unit.begin(); unitIter != _unit.end(); ++unitIter) {
		if (*unitIter != nullptr) {
			(*unitIter)->render();
		}
	}

	/* --------------------------------------------------------------------------- */
	/* stage 상태 출력 */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawText((int)SCREEN_BUFFER_INFO::width - 11, 1, "Stage: ");
	CScreenBuffer::getInstance()->drawText((int)SCREEN_BUFFER_INFO::width - 4, 1, _stage + '0');


	/* --------------------------------------------------------------------------- */
	/* 인게임 메뉴 작동 시, 메뉴 출력 */
	/* --------------------------------------------------------------------------- */
	if (_isMenuMode) {

		constexpr int menuWidth = 11;
		constexpr int menuHeight = 2;
		constexpr int menuX = (int)SCREEN_BUFFER_INFO::width / 2 - menuWidth / 2;
		constexpr int menuY = (int)SCREEN_BUFFER_INFO::height / 2 - menuHeight / 2;

		CScreenBuffer::getInstance()->drawBox(menuX, menuY, menuWidth, menuHeight);
		CScreenBuffer::getInstance()->drawText(menuX + 1, menuY + 1, "▷ 계속하기");
		CScreenBuffer::getInstance()->drawText(menuX + 1, menuY + 2, "▷ 메뉴가기");
		CScreenBuffer::getInstance()->drawText(menuX + 1, menuY + 1 + _menuIdx, "▶");
	} 

}

CGameScene::CGameScene() {

	_ignoreKeyPressing = false;
	_menuIdx = 0;
	_isMenuMode = false;
	_stage = 1;
	_processKill = false;

}