#include <stdio.h>
#include <time.h>

#include "Scene.h"
#include "TitleScene.h"
#include "ScreenBuffer.h"
#include "InputManager.h"

/* --------------------------------------------------------------------------- */
/* 현재 scene */
/* --------------------------------------------------------------------------- */
CScene* scene;

/* --------------------------------------------------------------------------- */
/* 다음에 바뀌어야할 scene */
/* --------------------------------------------------------------------------- */
CScene* nextScene;

void init() {

	scene = (CScene*)new CTitleScene();
	
	scene->init();
	
	nextScene = scene;

	srand(time(NULL));

}

int main() {

	init();

	while(scene->_processKill == false) {

		/* --------------------------------------------------------------------------- */
		/* 키보드 입력 받아 큐에 넣기 */
		/* --------------------------------------------------------------------------- */
		CInputManager::getInstance()->getKeyboardInput(scene->_ignoreKeyPressing);

		scene->update();
		scene->render();

		/* --------------------------------------------------------------------------- */
		/* 실제 버퍼 내용이 화면에 출력됨 */
		/* --------------------------------------------------------------------------- */
		CScreenBuffer::getInstance()->render();

		/* --------------------------------------------------------------------------- */
		/* scene 이 변경되었으면 반영 */
		/* --------------------------------------------------------------------------- */
		if (scene != nextScene) {
			delete scene;
			scene = nextScene;
			scene->init();
		}

		Sleep(100);

	}

	return 0;
}