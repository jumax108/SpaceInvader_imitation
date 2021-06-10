#include "GameOverScene.h"
#include "ScreenBuffer.h"
#include "InputManager.h"
#include "TitleScene.h"

void CGameOverScene::update() {

	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;
	while (keyboardQue->isEmpty() == false) {
		int msg;
		keyboardQue->pop(&msg);
		switch (msg) {
		case VK_RETURN:
			nextScene = (CScene*)new CTitleScene();
			break;
		}
	}
	

}

void CGameOverScene::render() {


	CScreenBuffer::getInstance()->clear();
	CScreenBuffer::getInstance()->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);

	CScreenBuffer::getInstance()->drawText(5, 5, "YOU DIE");
	CScreenBuffer::getInstance()->drawText(5, 10, "Press ENTER to continue");

}

CGameOverScene::CGameOverScene() {
	_ignoreKeyPressing = true;
}