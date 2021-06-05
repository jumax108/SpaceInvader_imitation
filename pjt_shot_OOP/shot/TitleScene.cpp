
#include <string.h>

#include "Queue.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "ScreenBuffer.h"

constexpr int menuBoxWidth = 14;
constexpr int menuBoxHeight = 3;
constexpr int menuBoxX = (int)SCREEN_BUFFER_INFO::width / 2 - menuBoxWidth / 2;
constexpr int menuBoxY = (int)SCREEN_BUFFER_INFO::height - menuBoxHeight - 4;

void CTitleScene::init() {

	CScreenBuffer* pScreenBuffer = CScreenBuffer::getInstance();

	pScreenBuffer->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);

	pScreenBuffer->drawBox(menuBoxX, menuBoxY, menuBoxWidth, menuBoxHeight);

	pScreenBuffer->drawText(10, 3, "SHOT");
	pScreenBuffer->drawText(menuBoxX + 1, menuBoxY + 1, "▷ 게임시작 ◁");
	pScreenBuffer->drawText(menuBoxX + 1, menuBoxY + 3, "▷ 게임종료 ◁");

	ignoreKeyPressing = true;
	processKill = false;

}

void CTitleScene::update() {

	CQueue* keyboardQue = CInputManager::getInstance()->keyboardQue;

	while (keyboardQue->isEmpty() == false) {

		int key;
		keyboardQue->pop(&key);

		switch (key) {

		case VK_UP:
		case VK_DOWN:
			menuIdx = 1 - menuIdx;
			break;

		case VK_RETURN: // enter
			switch (menuIdx) {
			case 0:
				// game start
				break;
			case 1:
				processKill = true;
				break;
			}
			break;

		}

	}

}

void CTitleScene::render() {

	CScreenBuffer::getInstance()->drawText(menuBoxX + 1 , menuBoxY + (menuIdx * 2 + 1)      , "▶");
	CScreenBuffer::getInstance()->drawText(menuBoxX + 13, menuBoxY + (menuIdx * 2 + 1)      , "◀");

	CScreenBuffer::getInstance()->drawText(menuBoxX + 1 , menuBoxY + (4 - (menuIdx * 2 + 1)), "▷");
	CScreenBuffer::getInstance()->drawText(menuBoxX + 13, menuBoxY + (4 - (menuIdx * 2 + 1)), "◁");

	CScreenBuffer::getInstance()->render();

}

CTitleScene::CTitleScene() {
	menuIdx = 0;
}