
#include <string.h>

#include "Queue.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "ScreenBuffer.h"
#include "GameScene.h"

constexpr int menuBoxWidth = 14;
constexpr int menuBoxHeight = 3;
constexpr int menuBoxX = (int)SCREEN_BUFFER_INFO::width / 2 - menuBoxWidth / 2;
constexpr int menuBoxY = (int)SCREEN_BUFFER_INFO::height - menuBoxHeight - 4;

void CTitleScene::init() {

	CScreenBuffer* pScreenBuffer = CScreenBuffer::getInstance();

	pScreenBuffer->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);

	pScreenBuffer->drawBox(menuBoxX, menuBoxY, menuBoxWidth, menuBoxHeight);

	constexpr int titleX = (int)SCREEN_BUFFER_INFO::width / 2 - 10;
	pScreenBuffer->drawText(titleX, 13, "SSSSS H   H  OOO  TTTTT");
	pScreenBuffer->drawText(titleX, 14, "S     H   H O   O   T  ");
	pScreenBuffer->drawText(titleX, 15, "SSSSS HHHHH O   O   T  ");
	pScreenBuffer->drawText(titleX, 16, "    S H   H O   O   T  ");
	pScreenBuffer->drawText(titleX, 17, "SSSSS H   H  OOO    T  ");
	pScreenBuffer->drawText(menuBoxX + 1, menuBoxY + 1, "▷ 게임시작 ◁");
	pScreenBuffer->drawText(menuBoxX + 1, menuBoxY + 3, "▷ 게임종료 ◁");

	_ignoreKeyPressing = true;
	_processKill = false;

}

void CTitleScene::update() {

	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;

	while (keyboardQue->isEmpty() == false) {

		int key;
		keyboardQue->pop(&key);

		switch (key) {

		case VK_UP:
		case VK_DOWN:
			_menuIdx = 1 - _menuIdx;
			break;

		case VK_RETURN: // enter
			switch (_menuIdx) {
			case 0:
				// game start
				nextScene = (CScene*)new CGameScene();
				break;
			case 1:
				_processKill = true;
				break;
			}
			break;

		}

	}

}

void CTitleScene::render() {

	CScreenBuffer::getInstance()->drawText(menuBoxX + 1 , menuBoxY + (_menuIdx * 2 + 1)      , "▶");
	CScreenBuffer::getInstance()->drawText(menuBoxX + 13, menuBoxY + (_menuIdx * 2 + 1)      , "◀");

	CScreenBuffer::getInstance()->drawText(menuBoxX + 1 , menuBoxY + (4 - (_menuIdx * 2 + 1)), "▷");
	CScreenBuffer::getInstance()->drawText(menuBoxX + 13, menuBoxY + (4 - (_menuIdx * 2 + 1)), "◁");

}

CTitleScene::CTitleScene() {
	_menuIdx = 0;
}