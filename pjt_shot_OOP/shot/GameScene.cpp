#include "GameScene.h"
#include "User.h"
#include "Enemy.h"
#include "InputManager.h"
#include "Queue.h"

constexpr int menuBoxWidth = 14;
constexpr int menuBoxHeight = 3;
constexpr int menuBoxX = (int)SCREEN_BUFFER_INFO::width / 2 - menuBoxWidth / 2;
constexpr int menuBoxY = (int)SCREEN_BUFFER_INFO::height - menuBoxHeight - 4;

void CGameScene::init() {


	_unit[0] = new CUser();
	for (int enemyCnt = 1, colCnt = 20; colCnt < (int)SCREEN_BUFFER_INFO::width-20; enemyCnt++, colCnt+=14) {
		_unit[enemyCnt] = new CEnemy(colCnt, 5);
	}
}

void CGameScene::update() {


	CQueue* keyboardQue = CInputManager::getInstance()->_keyboardQue;
	
	if (_menuMode == true) {
		while (keyboardQue->isEmpty() == false) {
			int msg;
			keyboardQue->pop(&msg);

			switch (msg) {
			case VK_ESCAPE:
				_menuMode = false;
				break;
			case VK_UP:
			case VK_DOWN:
				_menuIdx = 1 - _menuIdx;
			
				break;
			case VK_RETURN:
				break;
			}

		}
	}
	else {


		for (int unitCnt = 0; unitCnt < unitNum; ++unitCnt) {
			if (_unit[unitCnt] != nullptr) {
				_unit[unitCnt]->update();
			}
		}
	}

}

void CGameScene::render() {

	CScreenBuffer::getInstance()->clear();
	CScreenBuffer::getInstance()->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);

	for (int unitCnt = 0; unitCnt < unitNum; ++unitCnt) {
		if (_unit[unitCnt] != nullptr) {
			_unit[unitCnt]->render();
		}
	}

	if (_menuMode) {

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

	_menuIdx = 0;
	_menuMode = false;
	_stage = 1;
	_processKill = false;

	for (int unitCnt = 0; unitCnt < unitNum; ++unitCnt) {
		_unit[unitCnt] = nullptr;
	}

}