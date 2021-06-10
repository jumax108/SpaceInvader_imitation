#include "ClearScene.h"
#include "ScreenBuffer.h"
#include "InputManager.h"
#include "TitleScene.h"
#include "Queue.h"

void CClearScene::update() {

	/* --------------------------------------------------------------------------- */
	/* Ű���� �޽��� ó�� */
	/* --------------------------------------------------------------------------- */
	CQueue<int>* keyboardQue = CInputManager::getInstance()->_keyboardQue;
	while (keyboardQue->isEmpty() == false) {
		int msg;
		keyboardQue->pop(&msg);
		switch (msg) {
		case VK_RETURN:
			// ���͸� ������ Ÿ��Ʋ�� �̵�
			nextScene = (CScene*)new CTitleScene();
			break;
		}
	}


}

void CClearScene::render() {

	CScreenBuffer::getInstance()->clear();

	/* --------------------------------------------------------------------------- */
	/* Ŀ�ٶ� ȭ�� �ܰ� Ʋ */
	/* --------------------------------------------------------------------------- */
	CScreenBuffer::getInstance()->drawBox(0, 0, (int)SCREEN_BUFFER_INFO::width - 3, (int)SCREEN_BUFFER_INFO::height - 2);

	CScreenBuffer::getInstance()->drawText(5, 5, "CLEAR !!!");
	CScreenBuffer::getInstance()->drawText(5, 10, "Press ENTER to continue");

}

CClearScene::CClearScene() {
	_ignoreKeyPressing = true;
}