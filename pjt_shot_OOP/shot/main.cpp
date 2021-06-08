#include <stdio.h>

#include "Scene.h"
#include "TitleScene.h"
#include "ScreenBuffer.h"
#include "InputManager.h"

CScene* scene;
CScene* nextScene;

void init() {

	scene = (CScene*)new CTitleScene();
	
	scene->init();
	
	nextScene = scene;

}

int main() {

	init();

	while(scene->_processKill == false) {

		CInputManager::getInstance()->getKeyboardInput(scene->_ignoreKeyPressing);

		scene->update();
		scene->render();
		CScreenBuffer::getInstance()->render();

		if (scene != nextScene) {
			delete scene;
			scene = nextScene;
			scene->init();
		}

		Sleep(100);

	}

	return 0;
}