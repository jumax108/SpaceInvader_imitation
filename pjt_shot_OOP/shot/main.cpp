#include <stdio.h>

#include "Scene.h"
#include "TitleScene.h"
#include "ScreenBuffer.h"
#include "InputManager.h"

CScene* scene;

void init() {

	scene = (CScene*)new CTitleScene();
	
	scene->init();
	
}

int main() {

	init();

	while(scene->processKill == false) {

		CInputManager::getInstance()->getKeyboardInput(scene->ignoreKeyPressing);

		scene->update();
		scene->render();

		Sleep(100);

	}

	return 0;
}