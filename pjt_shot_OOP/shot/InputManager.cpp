#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Queue.h"
#include "InputManager.h"

CInputManager::CInputManager() {

	_keyboardQue = new CQueue(_queCap);

}

CInputManager::~CInputManager() {

	delete(_keyboardQue);

}

inline void getSingleKeyboardInput(bool ignoreKeyPressing, int vkey, bool* keyPressed, CQueue* keyboardQue) {

	short keyState = GetAsyncKeyState(vkey);

	if (keyState && (ignoreKeyPressing == false || *keyPressed == false)) {
		*keyPressed = true;
		keyboardQue->push(vkey);
	}
	else if(keyState == 0) {
		*keyPressed = false;
	}
}

#define SingleKeyInput(vkey) getSingleKeyboardInput(ignoreKeyPressing, vkey, &keyPressed[vkey], keyboardQue);

void CInputManager::getKeyboardInput(bool ignoreKeyPressing) {

	static bool keyPressed[256] = {false, };

	CQueue* keyboardQue = this->_keyboardQue;

	SingleKeyInput(VK_UP);
	SingleKeyInput(VK_DOWN);
	SingleKeyInput(VK_LEFT);
	SingleKeyInput(VK_RIGHT);
	SingleKeyInput(VK_RETURN);
	SingleKeyInput(VK_ESCAPE);

}