#include "ClearScene.h"
#include "ScreenBuffer.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "Queue.h"

void CClearScene::update() {

	/* --------------------------------------------------------------------------- */
	/* 키보드 메시지 처리 */
	/* --------------------------------------------------------------------------- */
	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;
	while (keyboardQue->isEmpty() == false) {
		int msg;
		keyboardQue->pop(&msg);
		switch (msg) {
		case VK_RETURN:
			// 엔터를 누르면 타이틀로 이동
			nextScene = (CScene*)new CTitleScene();
			break;
		}
	}


}

void CClearScene::render() {

	CScreenBuffer::getInstance()->clear();

	/* --------------------------------------------------------------------------- */
	/* 커다란 화면 외곽 틀 */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);

	CScreenBuffer::getInstance()->drawText(5, 5, "CLEAR !!!");
	CScreenBuffer::getInstance()->drawText(5, 10, "Press ENTER to continue");

}

CClearScene::CClearScene() {
	_ignoreKeyPressing = true;
}